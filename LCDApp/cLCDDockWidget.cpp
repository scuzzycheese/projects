#include <QtGui>
#include "cLCDDockWidget.h"
#include <iostream>

cLCDDockWidget::cLCDDockWidget(QWidget *parent) : QLCDNumber(parent)
{
	setStyleSheet
	(
		"QLCDNumber { border: 0px solid black; }"
	);
	setDigitCount(7);
	display("100:100");
}

//TODO: maybe work this out, so that the painter doesn't kill the borders
void cLCDDockWidget::resizeEvent(QResizeEvent *event)
{
	QString height;
	height.setNum(event->size().height());
	QString width;
	width.setNum(event->size().width());

	QString dimStr;
	dimStr += width;
	dimStr += ":";
	dimStr += height;
	display(dimStr);
}

cLCDDockWidget::~cLCDDockWidget()
{
}

