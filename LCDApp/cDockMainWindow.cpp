/* 
 * File:   cDockMainWindow.cpp
 * Author: scuzzy
 * 
 * Created on 08 July 2011, 11:04 PM
 */

#include "cDockMainWindow.h"
#include <QListWidget>
#include <QApplication>
#include <iostream>


cDockMainWindow::cDockMainWindow(QMainWindow *parent) : QMainWindow(parent)
{
	setDockOptions(QMainWindow::AnimatedDocks);
}

cDockMainWindow::cDockMainWindow()
{
	setDockOptions(QMainWindow::AnimatedDocks);
	setStyleSheet
	(
		"QMainWindow { border: 2px solid black; }"
		"QMainWindow::separator { width: 2px; height: 2px; background: black; }"
		"QDockWidget { border: 2px solid black; }"
		"QDockWidget::title {border: 1px solid black}"
	);
}

void cDockMainWindow::mousePressEvent(QMouseEvent *event)
{
	//This floating system needs to be implemented in a custom Dock widget
	if(event->button() == Qt::LeftButton && QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
	}
}


void cDockMainWindow::createDock()
{
	//for some reason, calling this in the constructor doesn't work
	setDockNestingEnabled(true);
	
	QDockWidget *dock0 = new QDockWidget(tr("Widget 0"), this);
	dock0->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::RightDockWidgetArea, dock0);

	QDockWidget *dock1 = new QDockWidget(tr("Widget 1"), this);
	dock1->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::RightDockWidgetArea, dock1);


	QDockWidget *dock2 = new QDockWidget(tr("Widget 2"), this);
	dock2->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::LeftDockWidgetArea, dock2);

}

cDockMainWindow::~cDockMainWindow()
{
}

