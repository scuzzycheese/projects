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
#include "cLM6800Proxy.h"

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	Ui::lcd ui;
	ui.setupUi(mainWindow);

	cVectorDrawWidget *drawArea = mainWindow->findChild<cVectorDrawWidget *>("drawPanel");

	cSerialTalk lcdPort;
	cLM6800Proxy test(&lcdPort);
	test.clearScreen();
	drawArea->setLM6800Proxy(&test);

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
