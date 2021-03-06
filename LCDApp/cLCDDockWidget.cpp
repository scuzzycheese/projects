#include <QtGui>
#include "cLCDDockWidget.h"
#include <iostream>
#include "cCustomDockWidget.h"

cLCDDockWidget::cLCDDockWidget(QWidget *parent, cPlugin *plug) : QLCDNumber(parent), plugin(plug)
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
/*
bool cLCDDockWidget::event(QEvent *e)
{
	std::cout << "EVENT: " << e->type() << std::endl;
	return QWidget::event(e);
}
 */

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
	if(parent->geometry().topRight().x() < parent->parentWidget()->geometry().width() - 2)
	{
		iWidth += 1;
	}
	//if(parent->geometry().bottomLeft().x() > ((cDockMainWindow *)(parent->parentWidget()))->geometry().bottomLeft().x())
	if(parent->geometry().bottomLeft().x() > 2)
	{
		iWidth += 1;
	}

	//if(parent->geometry().topRight().y() > ((cDockMainWindow *)(parent->parentWidget()))->geometry().topRight().y())
	if(parent->geometry().topRight().y() > 2)
	{
		iHeight += 1;
	}
	//if(parent->geometry().bottomLeft().y() < ((cDockMainWindow *)(parent->parentWidget()))->geometry().bottomLeft().y())
	if(parent->geometry().bottomLeft().y() < 126)
	{
		iHeight += 1;
	}


	sWidth.setNum(iWidth);
	sHeight.setNum(iHeight);

	//Only ask the plugins to update, if the dock isn't floating
	//TODO: fix the numbers
	if(!parent->isFloating())
	{
		plugin->setStartX(parent->geometry().topLeft().x() >> 1);
		plugin->setStartY(parent->geometry().topLeft().y() >> 1);
		plugin->setMaxX((parent->geometry().topLeft().x() + iWidth) >> 1);
		plugin->setMaxY((parent->geometry().topLeft().y() + iHeight) >> 1);
		plugin->setWidth(iWidth >> 1);
		plugin->setHeight(iHeight >> 1);

		//Maybe the clrScreen should be inside the reDraw method, not sure.
		plugin->clrScreen();
		plugin->reDraw();
	}

	QString dimStr;
	dimStr += sWidth;
	dimStr += ":";
	dimStr += sHeight;
	display(dimStr);
}

cLCDDockWidget::~cLCDDockWidget()
{
}

