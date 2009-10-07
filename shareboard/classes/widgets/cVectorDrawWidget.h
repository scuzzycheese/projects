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
		~cVectorDrawWidget();
		
		void setPenColor(const QColor &newColor);
		void setPenWidth(int newWidth);
	
		bool isModified() const { return modified; }
		QColor penColor() const { return myPenColor; }
		int penWidth() const { return myPenWidth; }
	
	public slots:
		void clearImage();
		void setPenColorSlot(const QColor &newColor);
		void setPenWidthSlot(int newWidth);
	
	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);
	
	private:
		void drawLine(const QPoint &startPoint, const QPoint &endPoint);
		void resizeImage(QImage *image, const QSize &newSize);
		
		bool modified;
		bool scribbling;
		int myPenWidth;
		QColor myPenColor;
		QImage image;
		QPoint lastPoint;

		//Matrix related stuff
		QMatrix *dDrawMat;
		deque<QVecLine> dLines;
		QVecLine *dTempLine;
		
};

#endif
