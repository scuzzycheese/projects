#ifndef CVECTORDRAWWIDGET_H
#define CVECTORDRAWWIDGET_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMatrix>
#include <iostream>
#include <deque>
#include "cVecLine.h"
#include "cEngine.h"

extern cEngine *engine;

using namespace std;

class cVectorDrawWidget : public QWidget
{
	Q_OBJECT


	//Data members
	private:
		
		bool dScribbling;
		bool dScrolling;
		int dCurrentPenWidth;
		QColor dCurrentPenColour;
		QImage dImage;
		
		//points that are important
		QPoint dLastPos;

	public:
		cVectorDrawWidget(QWidget *parent = 0);
		
		void setPenColor(const QColor &newColor);
		void setPenWidth(int newWidth);
	
		QColor penColor() const { return dCurrentPenColour; }
		int penWidth() const { return dCurrentPenWidth; }

		void translate(const QPoint &transBy);

	public slots:
		void clearImage();
		void setPenColorSlot(const QColor &newColor);
		void setPenWidthSlot(int newWidth);
		//void rotateSlot(const int &angle);
		void scaleSlot(const int &scale);
		void mResetMatrices();
	signals:
		void mMatrixChanged();
	
	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);
	
	private:
		void resizeImage(QImage *image, const QSize &newSize);
		
		
};

#endif
