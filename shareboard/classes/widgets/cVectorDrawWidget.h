#ifndef CVECTORDRAWWIDGET_H
#define CVECTORDRAWWIDGET_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMatrix>
#include <iostream>
#include <deque>
#include "QVecLine.h"


using namespace std;

class cVectorDrawWidget : public QWidget
{
	Q_OBJECT
	
	public:
		cVectorDrawWidget(QWidget *parent = 0);
		
		void setPenColor(const QColor &newColor);
		void setPenWidth(int newWidth);
	
		bool isModified() const { return modified; }
		QColor penColor() const { return myPenColor; }
		int penWidth() const { return myPenWidth; }

		void rotate(int angle, QPoint &point);
		void doScale(int scale, QPoint &point);

	
	public slots:
		void clearImage();
		void setPenColorSlot(const QColor &newColor);
		void setPenWidthSlot(int newWidth);
		void rotateSlot(int angle);
		void scaleSlot(int scale);
	
	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);
	
	private:
		void resizeImage(QImage *image, const QSize &newSize);
		
		bool modified;
		bool scribbling;
		int myPenWidth;
		QColor myPenColor;
		QImage image;
		QPoint lastPoint;

		//Matrix related stuff
		QMatrix dWorldMatrix;
		QMatrix dInvertedWorldMatrix;

		QMatrix dTranslationMatrix;
		QMatrix dRotationMatrix;
		QMatrix dScaleMatrix;

		deque<QVecLine> dLines;
		QVecLine *dTempLine;
		
};

#endif
