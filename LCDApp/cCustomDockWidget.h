/* 
 * File:   cCustomDockWidget.h
 * Author: scuzzy
 *
 * Created on 29 August 2011, 8:48 PM
 */
#include "cDockMainWindow.h"
#include <QDockWidget>
#include <iostream>

#ifndef _CCUSTOMDOCKWIDGET_H
#define	_CCUSTOMDOCKWIDGET_H

class cCustomDockWidget : public QDockWidget
{
public:
	cCustomDockWidget(QWidget *parent = 0);
	cCustomDockWidget(QString title, cDockMainWindow *mainWindow);
	virtual ~ cCustomDockWidget();
	//bool event(QEvent *e);
private:

};

#endif	/* _CCUSTOMDOCKWIDGET_H */

