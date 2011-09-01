/* 
 * File:   cCustomDockTitle.cpp
 * Author: scuzzy
 * 
 * Created on 31 August 2011, 4:52 PM
 */

#include "cCustomDockTitle.h"

cCustomDockTitle::cCustomDockTitle(QWidget *parent = 0) : QWidget(parent), parent(parent)
{
	QLabel *label = new QLabel(parent->windowTitle());
	QPushButton *buttonClose = new QPushButton("x");

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(label, 1);
	layout->addWidget(buttonClose);

	connect(buttonClose, SIGNAL(clicked()), parent, SLOT(close()));

	parentDockWidget = (cCustomDockWidget *)parentWidget();
}


void cCustomDockTitle::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(parentDockWidget->isFloating())
		{
			cursor = event->globalPos() - geometry().topLeft();
		}
		else
		{
			cursor = event->pos() - geometry().topLeft();
		}
	}
}

void cCustomDockTitle::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		parentDockWidget->setFloating(true);
		if(parentDockWidget->isFloating())
		{
			parent->move(event->globalPos() - cursor);
		}
		else
		{
			parent->move(event->pos() - cursor);
		}
		//parent->move(cursor);
	}
}


cCustomDockTitle::~cCustomDockTitle()
{
}




