#include <QtGui/QApplication>
#include <ui_lcd.h>
#include <QMainWindow>
#include "cSerialTalk.h"
#include "lcdFramework.h"
#include "cLM6800Proxy.h"
#include "cDockMainWindow.h"
#include "cPluginHandler.h"
#include "cPlugin.h"
#include "cQueue.h"
#include <iostream>

#include "plugins/testPlugin.h"

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	QMainWindow mainWindow;
	Ui::lcd ui;
	ui.setupUi(&mainWindow);

	cDrawWidget *drawArea = mainWindow.findChild<cDrawWidget *>("drawPanel");
	QWidget *realEstateTab = mainWindow.findChild<QTabWidget *>("realEstateTab");
	QFrame *pluginConfig = mainWindow.findChild<QFrame *>("pluginConfig");
	QListWidget *listWidget = mainWindow.findChild<QListWidget *>("pluginList");

	QPushButton *addPluginButton = mainWindow.findChild<QPushButton *>("addPluginToList");



	cSerialTalk lcdPort;
	cLM6800Proxy test(&lcdPort);
	test.clearScreen();








	cQueue queue;

	cDockMainWindow *docker = new cDockMainWindow();
	docker->createDock();

	cPluginHandler *plugHandler = new cPluginHandler(pluginConfig, listWidget, &queue, docker);
	plugHandler->setProxy(&test);

	plugHandler->addPlugin(getPluginInstance, getPluginName());

	//TODO: this concept needs to be tought out properly
	//plugHandler->setPluginActive(newPlugin);


	plugHandler->start();





	QObject::connect(addPluginButton, SIGNAL(clicked()), plugHandler, SLOT(addPluginToDock()));









	//test.clearScreen();
	drawArea->setLM6800Proxy(&test);

	std::cout << "struct lcdData size: " << sizeof(struct lcdData) << std::endl;
	struct lcdData lcdData = test.getLcdData();

	std::cout << "Width: " << lcdData.width << std::endl;
	std::cout << "Height: " << lcdData.height << std::endl;
	std::cout << "Colour: ";
	if(lcdData.colour) std::cout << "Yes";
	else std::cout << "No";
	std::cout << std::endl;
	std::cout << "BitDepth: " << (int)lcdData.bitDepth << std::endl;
	std::cout << "Backlight: ";
	if(lcdData.backlight) std::cout << "Yes";
	else std::cout << "No";
	std::cout << std::endl;




	mainWindow.show();
	docker->show();

	return app.exec();
}
