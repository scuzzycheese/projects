#include <QtGui>
#include "cVectorDrawWidget.h"
#include <iostream>

cVectorDrawWidget::cVectorDrawWidget(QWidget *parent) : QWidget(parent), dOperationTranslation(1, 0, 0, 1, 319, 164)
{
	setAttribute(Qt::WA_StaticContents);
	modified = false;
	scribbling = false;
	scrolling = false;
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
		//Set up the matrix to draw to, this is because
		//our world matrix could be rotated or moved or scaled.
		dInvertedWorldMatrix = dWorldMatrix.inverted();
		//create a new vector line object
		dTempLine = new QVecLine(myPenColor, myPenWidth);
		//Add this vector to he current line being drawn
		dTempLine->mAddVector(dInvertedWorldMatrix.map(event->pos()));

		scribbling = true;
	}
	if(event->button() == Qt::RightButton)
	{
		scrolling = true;
		lastPos = event->pos();
	}
}

void cVectorDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
	if((event->buttons() & Qt::LeftButton) && scribbling)
	{
		//Add this vector to he current line being drawn
		dTempLine->mAddVector(dInvertedWorldMatrix.map(event->pos()));
	}
	if((event->buttons() & Qt::RightButton) && scrolling)
	{
		QPoint diffPos = event->pos() - lastPos;
		translate(diffPos);
		lastPos = event->pos();
	}
}

void cVectorDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && scribbling)
	{
		//push the new line onto the deque.
		dLines.push_back(*dTempLine);
		//delete the old line
		delete(dTempLine);
		dTempLine = NULL;
		//Set the scribble state to false;
		scribbling = false;
	}
	if((event->buttons() & Qt::RightButton) && scrolling)
	{
		scrolling = false;
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
	double pi = 3.14159;
	 
	double a = pi/180 * (double)angle;
	double sina = sin(a);
	double cosa = cos(a);

	dRotationMatrix = dOperationTranslation.inverted() * QMatrix(cosa, sina, -sina, cosa, 0, 0) * dOperationTranslation;
	dWorldMatrix = dScaleMatrix * dRotationMatrix * dTranslationMatrix;
}


void cVectorDrawWidget::scaleSlot(const int &scale)
{
	dScale = 1 + ((double)scale / 10.0f);
	dScaleMatrix = dOperationTranslation.inverted() * QMatrix(dScale, 0, 0, dScale, 0, 0) * dOperationTranslation;
	dWorldMatrix = dScaleMatrix * dRotationMatrix * dTranslationMatrix;
}



void cVectorDrawWidget::translate(const QPoint &transBy)
{
	dTranslationMatrix.translate(transBy.x(), transBy.y());
	dWorldMatrix = dScaleMatrix * dRotationMatrix * dTranslationMatrix;
}
