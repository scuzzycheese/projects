/* 
 * File:   cDockMainWindow.cpp
 * Author: scuzzy
 * 
 * Created on 08 July 2011, 11:04 PM
 */

#include "cDockMainWindow.h"
#include <QListWidget>


cDockMainWindow::cDockMainWindow(QMainWindow *parent) : QMainWindow(parent)
{
	setWindowFlags(Qt::Widget);
}

cDockMainWindow::cDockMainWindow()
{
	setWindowFlags(Qt::Widget);
}



void cDockMainWindow::createDock()
{
 QDockWidget *dock = new QDockWidget(tr("Customers"), this);
 
     dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     QListWidget *customerList = new QListWidget(dock);
     customerList->addItems(QStringList()
             << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
             << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
             << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
             << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
             << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
             << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
     dock->setWidget(customerList);
     addDockWidget(Qt::RightDockWidgetArea, dock);




}

cDockMainWindow::~cDockMainWindow()
{
}

