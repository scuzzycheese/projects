#include <QtGui>
#include "cLCDDockWidget.h"

cLCDDockWidget::cLCDDockWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	dImage.fill(qRgb(255, 255, 255));
}

void cLCDDockWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawImage(QPoint(0, 0), dImage);
	update();
}

cLCDDockWidget::~cLCDDockWidget()
{
}

