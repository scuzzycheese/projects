#include <QtGui>
#include "cVectorDrawWidget.h"
#include <iostream>

cVectorDrawWidget::cVectorDrawWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	modified = false;
	scribbling = false;
	myPenWidth = 1;
	myPenColor = Qt::black;
	dDrawMat = new QMatrix();
	dLines = new deque<deque<QPoint> >();
	dTempLine = NULL;
}

cVectorDrawWidget::~cVectorDrawWidget()
{
	delete(dLines);
}


void cVectorDrawWidget::setPenColorSlot(const QColor &newColor)
{
	setPenColor(newColor);
}

void cVectorDrawWidget::setPenColor(const QColor &newColor)
{
	myPenColor = newColor;
}

void cVectorDrawWidget::setPenWidthSlot(int newWidth)
{
	setPenWidth(newWidth);
}
void cVectorDrawWidget::setPenWidth(int newWidth)
{
	myPenWidth = newWidth;
}

void cVectorDrawWidget::clearImage()
{
	image.fill(qRgb(255, 255, 255));
	modified = true;
	update();
}

void cVectorDrawWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		//lastPoint = event->pos();
		dTempLine = new deque<QPoint>;
		dTempLine->push_front(event->pos());

		scribbling = true;
	}
}

void cVectorDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
	if((event->buttons() & Qt::LeftButton) && scribbling)
	{
		//drawLineTo(event->pos());
		dTempLine->push_front(event->pos());
	}
}

void cVectorDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && scribbling)
	{
		//drawLineTo(event->pos());
		dTempLine->push_front(event->pos());
		dLines->push_front(*dTempLine);

		//memory cleanups
		delete(dTempLine);
		dTempLine = NULL;
		
		scribbling = false;
	}
}

void cVectorDrawWidget::paintEvent(QPaintEvent * /* event */)
{
	//Draw the lines currently being drawn
	

	//Draw the existing lines in the queue
	for(deque<deque<QPoint> >::iterator i = dLines->begin(); i < dLines->end(); i ++)
	{
		QPoint lastPoint = (*i)[0];
		for(deque<QPoint>::iterator j = (i->begin() + 1); j < i->end(); ++ j)
		{
			QPoint newPoint = *j;
			drawLine(lastPoint, newPoint);
			lastPoint = newPoint;
		}
	}
	QPainter painter(this);
	painter.drawImage(QPoint(0, 0), image);
	//TODO: maybe take the update line out of the drawLine function
	update();
}

void cVectorDrawWidget::resizeEvent(QResizeEvent *event)
{
	std::cout << "Resize!" << std::endl;
	if(width() > image.width() || height() > image.height())
	{
		int newWidth = qMax(width() + 128, image.width());
		int newHeight = qMax(height() + 128, image.height());
		resizeImage(&image, QSize(newWidth, newHeight));
		update();
	}
	QWidget::resizeEvent(event);
}

void cVectorDrawWidget::drawLine(const QPoint &startPoint, const QPoint &endPoint)
{
	QPainter painter(&image);
	painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(startPoint, endPoint);
	modified = true;
	
	int rad = (myPenWidth / 2) + 2;
	update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
	lastPoint = endPoint;
}

void cVectorDrawWidget::resizeImage(QImage *image, const QSize &newSize)
{
	if(image->size() == newSize) return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}

