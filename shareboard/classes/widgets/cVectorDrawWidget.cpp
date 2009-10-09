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
	dTempLine = NULL;
	dScale = 1.0f;
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
	myPenWidth = 1 + newWidth;
}

void cVectorDrawWidget::clearImage()
{
	dLines.clear();
	image.fill(qRgb(255, 255, 255));
	update();
}

void cVectorDrawWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		//lastPoint = event->pos();
		dInvertedWorldMatrix = dWorldMatrix.inverted();
		dTempLine = new QVecLine(myPenColor, myPenWidth);
		dTempLine->mAddVector(dInvertedWorldMatrix.map(event->pos()));

		scribbling = true;
	}
}

void cVectorDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
	if((event->buttons() & Qt::LeftButton) && scribbling)
	{
		//drawLineTo(event->pos());
		dTempLine->mAddVector(dInvertedWorldMatrix.map(event->pos()));
	}
}

void cVectorDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && scribbling)
	{
		//drawLineTo(event->pos());
		dTempLine->mAddVector(dInvertedWorldMatrix.map(event->pos()));
		dLines.push_back(*dTempLine);

		//memory cleanups
		delete(dTempLine);
		dTempLine = NULL;
		
		scribbling = false;
	}
}

void cVectorDrawWidget::paintEvent(QPaintEvent * /* event */)
{
	image.fill(qRgb(255, 255, 255));
	//Draw the existing lines in the queue
	for(deque<QVecLine>::iterator i = dLines.begin(); i < dLines.end(); i ++)
	{
		(*i).mDraw(image, dWorldMatrix, dScale);
	}

	//Draw the lines currently being drawn
	if(dTempLine) dTempLine->mDraw(image, dWorldMatrix, dScale);

	QPainter painter(this);
	//painter.setMatrix(dWorldMatrix);
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

void cVectorDrawWidget::rotateSlot(const int &angle)
{
	//this point needs to be dynamic in future
	QPoint point(319, 164);
	rotate(angle, point);

	dWorldMatrix = dScaleMatrix * dRotationMatrix * dTranslationMatrix;

}

void cVectorDrawWidget::rotate(const int &angle, const QPoint &point)
{

	//This is the matrix for transforming against an arbitrary point
	//This matrix, AND it's inverted counterpart, should really be 
	//calculated once.
	QMatrix arbTranslationMatrix(1, 0, 0, 1, (double)point.x(), (double)point.y());
	//cout << "Angle: " << angle << endl;
	
	double pi = 3.14159;
	 
	double a    = pi/180 * (double)angle;
	double sina = sin(a);
	double cosa = cos(a);

	QMatrix rotationMatrix(cosa, sina, -sina, cosa, 0, 0);
	
	dRotationMatrix = arbTranslationMatrix.inverted() * rotationMatrix * arbTranslationMatrix;
}


void cVectorDrawWidget::scaleSlot(const int &scale)
{
	dScale = 1 + ((double)scale / 10.0f);

	QPoint point(319, 164);
	doScale(point);

	dWorldMatrix = dScaleMatrix * dRotationMatrix * dTranslationMatrix;
}

void cVectorDrawWidget::doScale(const QPoint &point)
{
	QMatrix arbTranslationMatrix(1, 0, 0, 1, (double)point.x(), (double)point.y());

	dScaleMatrix = arbTranslationMatrix.inverted() * QMatrix(dScale, 0, 0, dScale, 0, 0) * arbTranslationMatrix;
}

