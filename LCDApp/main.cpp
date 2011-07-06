/*
 * File:   main.cpp
 * Author: scuzzy
 *
 * Created on 29 June 2011, 9:24 PM
 */

#include <QtGui/QApplication>
#include <ui_lcd.h>
#include <QMainWindow>
#include "cSerialTalk.h"
#include "lcdFramework.h"
#include "cLM6800Proxy.h"
#include <iostream>

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	Ui::lcd ui;
	ui.setupUi(mainWindow);

	cVectorDrawWidget *drawArea = mainWindow->findChild<cVectorDrawWidget *>("drawPanel");
	drawArea->setPenWidth(3);

	cSerialTalk lcdPort;
	cLM6800Proxy test(&lcdPort);
	test.clearScreen();
	drawArea->setLM6800Proxy(&test);

	std::cout << "struct lcdData size: " << sizeof(struct lcdData) << std::endl;
	struct lcdData lcdData = test.getLcdData();

	std::cout << "Width: " << lcdData.width << std::endl;
	std::cout << "Height: " << lcdData.height << std::endl;

	mainWindow->show();


	/*
	while(1)
	{
		lcdPort.write("x", 1);
		sleep(1);
		lcdPort.write("c", 1);
		sleep(1);
		lcdPort.write("b", 1);
		sleep(1);
		lcdPort.write("c", 1);
	}
	 */

	//test.setPixel(100, 20);


	// create and show your widgets here

	return app.exec();
}
