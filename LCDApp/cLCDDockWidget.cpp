#include <QtGui>
#include "cLCDDockWidget.h"
#include <iostream>

cLCDDockWidget::cLCDDockWidget(QWidget *parent) : QWidget(parent)
{
	setStyleSheet
	(
		"QWidget { border: 2px solid black; }"
	);
	setAttribute(Qt::WA_StaticContents);
	dImage.fill(qRgb(127, 127, 127));
}

void cLCDDockWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawImage(QPoint(2, 2), dImage);
	update();
}

//TODO: maybe work this out, so that the painter doesn't kill the borders
void cLCDDockWidget::resizeEvent(QResizeEvent *event)
{
	//resizeImage(&dImage, event->size());
	resizeImage(&dImage, QSize((width() > 4) ? width() - 4 : 1, (height() > 4) ? height() - 4 : 1));

	//std::cout << "WIDTH: " << width() << std::endl;
	//std::cout << "HEIGHT: " << height() << std::endl;
	/*
	if(width() > dImage.width() || height() > dImage.height())
	{
		int newWidth = qMax(width() + 128, dImage.width());
		int newHeight = qMax(height() + 128, dImage.height());
		resizeImage(&dImage, QSize(newWidth, newHeight));
		update();
	}
	 */
	update();
	QWidget::resizeEvent(event);
}

void cLCDDockWidget::resizeImage(QImage *image, const QSize &newSize)
{
	if(image->size() == newSize) return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(127, 127, 127));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(2, 2), *image);
	*image = newImage;
}

cLCDDockWidget::~cLCDDockWidget()
{
}

