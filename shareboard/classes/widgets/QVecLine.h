#ifndef QVECLINE_H
#define QVEVLINE_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QImage>
#include <QPainter>
#include <iostream>
#include <deque>

using namespace std;

class QVecLine
{
	private:
		deque<QPoint> dLine;
		QColor dColour;
		int dDiameter;
		QPoint *lastPoint;

		void mDrawLine(QImage &image, const QPoint &startPoint, const QPoint &endPoint);

	public:
		QVecLine();
		QVecLine(QColor colour, int diameter);
		~QVecLine();
		void mDraw(QImage &image, QMatrix &mat);
		void mAddVector(const QPoint &newVec);

};

#endif
