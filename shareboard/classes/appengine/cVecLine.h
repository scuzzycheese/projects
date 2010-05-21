#ifndef CVECLINE_H
#define CVECLINE_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QImage>
#include <QPainter>
#include <iostream>
#include <deque>

using namespace std;

class cVecLine
{
private:
	deque<QPoint> dLine;
	QColor dColour;
	int dDiameter;
	QPoint *dLastPoint;

	void mDrawLine(QImage &image, const QPoint &startPoint, const QPoint &endPoint, double thicknesScale);

public:
	cVecLine();
	cVecLine(QColor colour, int diameter);
	~cVecLine();
	void mDraw(QImage &image, QMatrix &mat, double thicknesScale);
	void mAddVector(const QPoint &newVec);

};

#endif
