/* 
 * File:   cCustomDockWidget.cpp
 * Author: scuzzy
 * 
 * Created on 29 August 2011, 8:48 PM
 */

#include "cCustomDockWidget.h"


cCustomDockWidget::cCustomDockWidget(QWidget *parent) : QDockWidget(parent)
{
}
cCustomDockWidget::cCustomDockWidget(QString title, cDockMainWindow *mainWindow)
{
	QDockWidget(title, mainWindow);

	QWidget *titleBar = new QWidget(this);
	setTitleBarWidget(titleBar);
}


cCustomDockWidget::~cCustomDockWidget()
{
}

