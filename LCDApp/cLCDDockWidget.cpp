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

	QString sHeight;
	QString sWidth;

	int iHeight;
	int iWidth;

	iHeight = parent->size().height();
	iWidth = parent->size().width();


	//if(parent->geometry().topRight().x() < ((cDockMainWindow *)(parent->parentWidget()))->geometry().topRight().x())
	if(parent->geometry().topRight().x() < parent->parentWidget()->geometry().width() - 4)
	{
		iWidth += 1;
	}
	//if(parent->geometry().bottomLeft().x() > ((cDockMainWindow *)(parent->parentWidget()))->geometry().bottomLeft().x())
	if(parent->geometry().bottomLeft().x() > 4)
	{
		iWidth += 1;
	}

	//if(parent->geometry().topRight().y() > ((cDockMainWindow *)(parent->parentWidget()))->geometry().topRight().y())
	if(parent->geometry().topRight().y() > 4)
	{
		iHeight += 1;
	}
	//if(parent->geometry().bottomLeft().y() < ((cDockMainWindow *)(parent->parentWidget()))->geometry().bottomLeft().y())
	if(parent->geometry().bottomLeft().y() < 252)
	{
		iHeight += 1;
	}


	sWidth.setNum(iWidth);
	sHeight.setNum(iHeight);


	QString dimStr;
	dimStr += sWidth;
	dimStr += ":";
	dimStr += sHeight;
	display(dimStr);
}

cLCDDockWidget::~cLCDDockWidget()
{
}

