/* 
 * File:   cCustomDockWidget.cpp
 * Author: scuzzy
 * 
 * Created on 29 August 2011, 8:48 PM
 */

#include "cCustomDockWidget.h"
#include "cCustomDockTitle.h"


cCustomDockWidget::cCustomDockWidget(QWidget *parent) : QDockWidget(parent)
{
}
cCustomDockWidget::cCustomDockWidget(QString title, cDockMainWindow *mainWindow)
{
/*
	setStyleSheet
	(
		//"QDockWidget { border: 2px solid black; }"
		//"QDockWidget::title {border-bottom: 1px solid black}"
	);
 */

	QDockWidget(title, mainWindow);

	//Remove the title bar
	//cCustomDockTitle *titleBar = new cCustomDockTitle(this);
	//setTitleBarWidget(titleBar);
}

/*
bool cCustomDockWidget::event(QEvent *e)
{
	std::cout << "EVENT: " << e->type() << std::endl;
	return QWidget::event(e);
}
 */

cCustomDockWidget::~cCustomDockWidget()
{
}

