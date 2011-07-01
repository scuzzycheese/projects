/*
 * File:   main.cpp
 * Author: scuzzy
 *
 * Created on 29 June 2011, 9:24 PM
 */

#include <QtGui/QApplication>
#include <ui_lcd.h>
#include <QMainWindow>

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	Ui::lcd ui;
	ui.setupUi(mainWindow);

	mainWindow->show();

	// create and show your widgets here

	return app.exec();
}
