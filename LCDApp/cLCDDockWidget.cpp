#include <QtGui>
#include "cLCDDockWidget.h"
#include <iostream>
#include "cCustomDockWidget.h"

cLCDDockWidget::cLCDDockWidget(QWidget *parent) : QLCDNumber(parent)
{
	/*
	setStyleSheet
	(
		"QLCDNumber { border: 2px solid black; }"
	);
	 */
	setDigitCount(7);
	display("100:100");
}

//TODO: maybe work this out, so that the painter doesn't kill the borders
void cLCDDockWidget::resizeEvent(QResizeEvent *event)
{
	cCustomDockWidget *parent = (cCustomDockWidget *)parentWidget();

	QString height;
	//height.setNum(event->size().height());
	if(parent->size().height() < ((cDockMainWindow *)(parent->parentWidget()))->geometry().height())
	{
		height.setNum(parent->size().height() + 1);
	}
	else
	{
		height.setNum(parent->size().height());
	}

	QString width;
	//width.setNum(event->size().width());
	if(parent->size().width() < ((cDockMainWindow *)(parent->parentWidget()))->geometry().width())
	{
		width.setNum(parent->size().width() + 1);
	}
	else
	{
		width.setNum(parent->size().width());
	}


	QString dimStr;
	dimStr += width;
	dimStr += ":";
	dimStr += height;
	display(dimStr);
}

cLCDDockWidget::~cLCDDockWidget()
{
}

