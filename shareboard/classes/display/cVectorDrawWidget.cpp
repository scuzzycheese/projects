#include <QtGui>
#include "cVectorDrawWidget.h"
#include <iostream>

cVectorDrawWidget::cVectorDrawWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	dScribbling = false;
	dScrolling = false;
	dCurrentPenWidth = 1;
	dCurrentPenColour = Qt::black;
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
	engine->mClear();
	dImage.fill(qRgb(255, 255, 255));
	update();
}
void cVectorDrawWidget::mResetMatrices()
{
	QDial *angleDial = nativeParentWidget()->findChild<QDial *>("orientation");
	angleDial->setValue(0);

	QSlider *scale = nativeParentWidget()->findChild<QSlider *>("scale");	
	scale->setValue(0);

	engine->mResetMatrices();
	if(engine->mMatrixChanged()) emit mMatrixChanged();
}

void cVectorDrawWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		//Set up the matrix to draw to, this is because
		//our world matrix could be rotated or moved or scaled.

		//TODO: Eventually the matrix inversion will take plave inside the
		//mStartNewLine method, because the engine will be the thing controlling
		//the matrices
		engine->mStartNewLine(event->pos(), dCurrentPenColour, dCurrentPenWidth);

		dScribbling = true;
	}
	if(event->button() == Qt::RightButton)
	{
		dScrolling = true;
		dLastPos = event->pos();
	}
}

void cVectorDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
	if((event->buttons() & Qt::LeftButton) && dScribbling)
	{
		engine->mAddVectToLine(event->pos());
	}
	if((event->buttons() & Qt::RightButton) && dScrolling)
	{
		QPoint diffPos = event->pos() - dLastPos;
		translate(diffPos);
		dLastPos = event->pos();
	}
}

void cVectorDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && dScribbling)
	{
		engine->mEndNewLine();
		//Set the scribble state to false;
		dScribbling = false;
	}
	if((event->buttons() & Qt::RightButton) && dScrolling)
	{
		dScrolling = false;
	}
}

void cVectorDrawWidget::paintEvent(QPaintEvent * /* event */)
{
	dImage.fill(qRgb(255, 255, 255));

	deque<cVecLine> *lines = engine->mGetLines();
	//Draw the existing lines in the queue
	for(deque<cVecLine>::iterator i = (*lines).begin(); i < (*lines).end(); i ++)
	{
		(*i).mDraw(dImage, engine->dWorldMatrix, engine->dScale);
	}

	//Draw the lines currently being drawn
	if(engine->mGetCurrentLine()) engine->mGetCurrentLine()->mDraw(dImage, engine->dWorldMatrix, engine->dScale);

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

void cVectorDrawWidget::scaleSlot(const int &scale)
{
	engine->mScale(scale);
	if(engine->mMatrixChanged()) emit mMatrixChanged();
}

void cVectorDrawWidget::translate(const QPoint &transBy)
{
	engine->mTranslate(transBy);
	if(engine->mMatrixChanged()) emit mMatrixChanged();
}
