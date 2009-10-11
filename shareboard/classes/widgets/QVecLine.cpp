#include "QVecLine.h"


QVecLine::QVecLine(QColor colour, int diameter) : dLastPoint(NULL)
{
	dColour = colour;
	dDiameter = diameter;
}


QVecLine::QVecLine() : dLastPoint(NULL)
{
	dColour = Qt::black;
	dDiameter = 1;
}

QVecLine::~QVecLine()
{
}


void QVecLine::mDraw(QImage &image, QMatrix &mat, double thicknesScale)
{
	for(deque<QPoint>::iterator i = dLine.begin(); i < dLine.end(); ++ i)
	{
		QPoint &newPoint = *i;
		if(dLastPoint) mDrawLine(image, mat.map(*dLastPoint), mat.map(newPoint), thicknesScale);
		dLastPoint = &newPoint;
	}
	dLastPoint = NULL;
}

void QVecLine::mDrawLine(QImage &image, const QPoint &startPoint, const QPoint &endPoint, double thicknesScale)
{
	QPainter painter(&image);
	painter.setPen(QPen(dColour, dDiameter * thicknesScale, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(startPoint, endPoint);
}


void QVecLine::mAddVector(const QPoint &newVec)
{
	dLine.push_back(newVec);
}

