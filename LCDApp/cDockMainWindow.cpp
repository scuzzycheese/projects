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
#include "cLCDDockWidget.h"
#include "cDrawWidget.h"
#include "cCustomDockWidget.h"


cDockMainWindow::cDockMainWindow(QMainWindow *parent) : QMainWindow(parent)
{
}

cDockMainWindow::cDockMainWindow()
{
	setDockOptions(QMainWindow::AnimatedDocks);
	setStyleSheet
	(
		"QMainWindow { border: 2px solid black; }"
		"QMainWindow::separator { width: 2px; height: 2px; background: black; }"
	);

	setMinimumHeight(128);
	setMaximumHeight(128);

	setMinimumWidth(512);
	setMaximumWidth(512);
}

/*
bool cDockMainWindow::event(QEvent *e)
{
	std::cout << "EVENT: " << e->type() << std::endl;
	return QWidget::event(e);
	//return false;
}
 */

void cDockMainWindow::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
	}
}


void cDockMainWindow::createDock()
{
	//for some reason, calling this in the constructor doesn't work
	setDockNestingEnabled(true);


/*
	cCustomDockWidget *dock0 = new cCustomDockWidget(tr("Widget 0"), this);
	dock0->setAllowedAreas(Qt::AllDockWidgetAreas);
	cLCDDockWidget *lcdWid0 = new cLCDDockWidget(dock0);
	dock0->setWidget(lcdWid0);
	addDockWidget(Qt::RightDockWidgetArea, dock0);

	cCustomDockWidget *dock1 = new cCustomDockWidget(tr("Widget 1"), this);
	dock1->setAllowedAreas(Qt::AllDockWidgetAreas);
	cLCDDockWidget *lcdWid1 = new cLCDDockWidget(dock1);
	dock1->setWidget(lcdWid1);
	addDockWidget(Qt::RightDockWidgetArea, dock1);


	cCustomDockWidget *dock2 = new cCustomDockWidget(tr("Widget 2"), this);
	dock2->setAllowedAreas(Qt::AllDockWidgetAreas);
	cLCDDockWidget *lcdWid2 = new cLCDDockWidget(dock2);
	dock2->setWidget(lcdWid2);
	addDockWidget(Qt::LeftDockWidgetArea, dock2);
 */

}



void cDockMainWindow::addPluginToDock(cPlugin *plugin)
{
	std::cout << "adding plugin to dock" << std::endl;
	cCustomDockWidget *dock = new cCustomDockWidget(plugin->getName(), this);
	dock->setAllowedAreas(Qt::AllDockWidgetAreas);

	cLCDDockWidget *lcdWid = new cLCDDockWidget(dock);
	dock->setWidget(lcdWid);

	addDockWidget(Qt::RightDockWidgetArea, dock);
}

cDockMainWindow::~cDockMainWindow()
{
}

