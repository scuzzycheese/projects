#include <QtGui>
#include "cVectorDrawWidget.h"
#include <iostream>

cVectorDrawWidget::cVectorDrawWidget(QWidget *parent) : QWidget(parent), dOperationTranslation(1, 0, 0, 1, 319, 164)
{
	setAttribute(Qt::WA_StaticContents);
	dScribbling = false;
	dScrolling = false;
	dCurrentPenWidth = 1;
	dCurrentPenColour = Qt::black;
	dTempLine = NULL;
	dScale = 1.0f;
}



QMatrix *cVectorDrawWidget::mGetWorldMatrix()
{
	return &dWorldMatrix;
}
QMatrix *cVectorDrawWidget::mGetTranslationMatrix()
{
	return &dTranslationMatrix;
}
QMatrix *cVectorDrawWidget::mGetScaleMatrix()
{
	return &dScaleMatrix;
}
QMatrix *cVectorDrawWidget::mGetRotationMatrix()
{
	return &dRotationMatrix;
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
	dLines.clear();
	dImage.fill(qRgb(255, 255, 255));
	update();
}
void cVectorDrawWidget::mResetMatrices()
{
	QDial *angleDial = nativeParentWidget()->findChild<QDial *>("orientation");
	angleDial->setValue(0);

	QSlider *scale = nativeParentWidget()->findChild<QSlider *>("scale");	
	scale->setValue(0);

	dWorldMatrix.reset();
	dInvertedWorldMatrix.reset();
	dRotationMatrix.reset();
	dTranslationMatrix.reset();
	dScaleMatrix.reset();
	dOperationTranslation.setMatrix(1, 0, 0, 1, 319, 164);
	dScale = 1.0f;
	emit mMatrixChanged();
}

void cVectorDrawWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		//Set up the matrix to draw to, this is because
		//our world matrix could be rotated or moved or scaled.
		dInvertedWorldMatrix = dWorldMatrix.inverted();
		//create a new vector line object
		dTempLine = new QVecLine(dCurrentPenColour, dCurrentPenWidth);
		//Add this vector to he current line being drawn
		dTempLine->mAddVector(dInvertedWorldMatrix.map(event->pos()));

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
		//Add this vector to he current line being drawn
		dTempLine->mAddVector(dInvertedWorldMatrix.map(event->pos()));
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
		//push the new line onto the deque.
		dLines.push_back(*dTempLine);
		//delete the old line
		delete(dTempLine);
		dTempLine = NULL;
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
	//Draw the existing lines in the queue
	for(deque<QVecLine>::iterator i = dLines.begin(); i < dLines.end(); i ++)
	{
		(*i).mDraw(dImage, dWorldMatrix, dScale);
	}

	//Draw the lines currently being drawn
	if(dTempLine) dTempLine->mDraw(dImage, dWorldMatrix, dScale);

	QPainter painter(this);
	//painter.setMatrix(dWorldMatrix);
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

/*
void cVectorDrawWidget::rotateSlot(const int &angle)
{
	double pi = 3.14159;
	 
	double a = pi/180 * (double)angle;
	double sina = sin(a);
	double cosa = cos(a);





	dRotationMatrix = QMatrix(cosa, sina, -sina, cosa, 0, 0);
	QMatrix newTrans = dOperationTranslation.inverted() * dTranslationMatrix * dRotationMatrix * dOperationTranslation;
	QPoint transVector(newTrans.dx() - dTranslationMatrix.dx(), newTrans.dy() - dTranslationMatrix.dy());
	translate(transVector);





	dRotationMatrix = QMatrix(cosa, sina, -sina, cosa, 0, 0);
	mDumpMatrix("dOperationTranslation", dOperationTranslation);
	mDumpMatrix("dTranslationMatrix", dTranslationMatrix);
	mDumpMatrix("dRotationMatrix", dRotationMatrix);
	dTranslationMatrix = dOperationTranslation.inverted() * dTranslationMatrix * dRotationMatrix * dOperationTranslation;
	mSetRotationToIdentity(dTranslationMatrix);
	dWorldMatrix = dScaleMatrix * dRotationMatrix * dTranslationMatrix;
	emit mMatrixChanged();

}
*/


void cVectorDrawWidget::scaleSlot(const int &scale)
{
	dScale = 1 + ((double)scale / 10.0f);
	dScaleMatrix = dOperationTranslation.inverted() * QMatrix(dScale, 0, 0, dScale, 0, 0) * dOperationTranslation;
	dWorldMatrix = dScaleMatrix * dTranslationMatrix;
	emit mMatrixChanged();
}



void cVectorDrawWidget::translate(const QPoint &transBy)
{
	//I think this needs to be here, because scaling performs quite complex
	//operations on the matrix, the scale matrix has to be updated with
	//every translation operation
	dScaleMatrix = dOperationTranslation.inverted() * QMatrix(dScale, 0, 0, dScale, 0, 0) * dOperationTranslation;


	QMatrix tempMatrix = dScaleMatrix;
	tempMatrix.setMatrix(tempMatrix.m11(), tempMatrix.m12(), tempMatrix.m21(), tempMatrix.m22(), 0, 0);
	QPointF tempPoint = tempMatrix.inverted().map(QPointF(transBy));
	

	dOperationTranslation.translate(-tempPoint.x(), -tempPoint.y());
	dTranslationMatrix.translate(tempPoint.x(), tempPoint.y());

	dWorldMatrix = dScaleMatrix * dTranslationMatrix;
	emit mMatrixChanged();
}

void cVectorDrawWidget::mSetRotationToIdentity(QMatrix &mat)
{
	QPointF holdPoint(mat.dx(), mat.dy());
	mat.setMatrix(1, 0, 0, 1, holdPoint.x(), holdPoint.y());
}

void cVectorDrawWidget::mDumpMatrix(string name, QMatrix &mat)
{
	cout << name << ": ";
	cout << mat.m11() << ", ";
	cout << mat.m12() << ", ";
	cout << mat.m21() << ", ";
	cout << mat.m22() << ", ";
	cout << mat.dx() << ", ";
	cout << mat.dy() << endl;
}
