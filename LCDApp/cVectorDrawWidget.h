#ifndef CVECTORDRAWWIDGET_H
#define CVECTORDRAWWIDGET_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMatrix>
#include <iostream>
#include <deque>
#include "cLM6800Proxy.h"


using namespace std;

class cDrawWidget : public QWidget
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

		cLM6800Proxy *lcdProxy;



	public:

		void setLM6800Proxy(cLM6800Proxy *prox);

		cDrawWidget(QWidget *parent = 0);
		
		void setPenColor(const QColor &newColor);
		void setPenWidth(int newWidth);
	
		QColor penColor() const { return dCurrentPenColour; }
		int penWidth() const { return dCurrentPenWidth; }


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
		void resizeImage(QImage *image, const QSize &newSize);
		
		
};

#endif
