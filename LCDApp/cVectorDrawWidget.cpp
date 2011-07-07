#include <QtGui>
#include "cVectorDrawWidget.h"
#include <iostream>
#include "cSerialTalk.h"

cVectorDrawWidget::cVectorDrawWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	dScribbling = false;
	dScrolling = false;
	dCurrentPenWidth = 1;
	dCurrentPenColour = Qt::black;
	dImage.fill(qRgb(255, 255, 255));
}

void cVectorDrawWidget::setLM6800Proxy(cLM6800Proxy *prox)
{
	lcdProxy = prox;
}
void cVectorDrawWidget::setPenColorSlot(const QColor &newColor)
{
	setPenColor(newColor);
}

void cVectorDrawWidget::setPenColor(const QColor &newColor)
{
	dCurrentPenColour = newColor;
}

void cVectorDrawWidget::setPenWidthSlot(int newWidth)
{
	setPenWidth(newWidth);
}
void cVectorDrawWidget::setPenWidth(int newWidth)
{
	dCurrentPenWidth = 1 + newWidth;
}

void cVectorDrawWidget::clearImage()
{
	dImage.fill(qRgb(255, 255, 255));
	update();
}

void cVectorDrawWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		dLastPos = event->pos();
	}
}

void cVectorDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
	int xReal = event->pos().x();
	int yReal = event->pos().y();
	if(xReal > 0 && xReal < 512 && yReal > 0 && yReal < 128)
	{
		uint8_t x = xReal >> 1;
		uint8_t y = yReal >> 1;
		lcdProxy->setPixel(x, y);
		QPainter painter(&dImage);
		painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter.drawLine(dLastPos, event->pos());
	}
	dLastPos = event->pos();
}

void cVectorDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QPainter painter(&dImage);
	painter.drawLine(dLastPos, event->pos());
	dLastPos = event->pos();
}

void cVectorDrawWidget::paintEvent(QPaintEvent * /* event */)
{
	QPainter painter(this);
	painter.drawImage(QPoint(0, 0), dImage);
	//TODO: maybe take the update line out of the drawLine function
	update();
}

void cVectorDrawWidget::resizeEvent(QResizeEvent *event)
{
	if(width() > dImage.width() || height() > dImage.height())
	{
		int newWidth = qMax(width() + 128, dImage.width());
		int newHeight = qMax(height() + 128, dImage.height());
		resizeImage(&dImage, QSize(newWidth, newHeight));
		update();
	}
	QWidget::resizeEvent(event);
}


//TODO: refactor this to redraw with vectors instead
void cVectorDrawWidget::resizeImage(QImage *image, const QSize &newSize)
{
	if(image->size() == newSize) return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}