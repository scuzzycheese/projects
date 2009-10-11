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

		void translate(const QPoint &transBy);
	
	public slots:
		void clearImage();
		void setPenColorSlot(const QColor &newColor);
		void setPenWidthSlot(int newWidth);
		void rotateSlot(const int &angle);
		void scaleSlot(const int &scale);
	
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
		bool scrolling;
		int myPenWidth;
		QColor myPenColor;
		QImage image;
		
		//points that are important
		QPoint lastPos;
		QMatrix dOperationTranslation;

		//Matrix related stuff
		QMatrix dWorldMatrix;
		QMatrix dInvertedWorldMatrix;

		QMatrix dTranslationMatrix;
		QMatrix dRotationMatrix;
		QMatrix dScaleMatrix;

		double dScale;

		deque<QVecLine> dLines;
		QVecLine *dTempLine;
		
};

#endif
