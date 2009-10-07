#include "QVecLine.h"


QVecLine::QVecLine(QColor colour, int diameter) : lastPoint(NULL)
{
	dColour = colour;
	dDiameter = diameter;
}


QVecLine::QVecLine() : lastPoint(NULL)
{
	dColour = Qt::black;
	dDiameter = 1;
}

QVecLine::~QVecLine()
{
}


void QVecLine::mDraw(QImage &image)
{
	for(deque<QPoint>::iterator i = dLine.begin(); i < dLine.end(); ++ i)
	{
		QPoint &newPoint = *i;
		if(lastPoint) mDrawLine(image, *lastPoint, newPoint);
		lastPoint = &newPoint;
	}
	lastPoint = NULL;
}

void QVecLine::mDrawLine(QImage &image, const QPoint &startPoint, const QPoint &endPoint)
{
	QPainter painter(&image);
	painter.setPen(QPen(dColour, dDiameter, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(startPoint, endPoint);
}


void QVecLine::mAddVector(const QPoint &newVec)
{
	dLine.push_back(newVec);
}

