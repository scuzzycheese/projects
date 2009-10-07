#include "QLine.h"


QLine::QLine(QColor colour, int diameter)
{
	dLine = new deque<QPoint>();
	dColour = colour;
	dDiameter = diameter;
}


QLine::QLine()
{
	dLine = new deque<QPoint>();
	dColour = Qt::black;
	dDiameter = 1;
}

QLine::~QLine()
{
	delete(dLine);
}


void draw(QImage &image)
{
	//TODO: finish this function to draw the entire line
	QPoint lastPoint = dLine[0];
}

void QLine::drawLine(QImage &image, const QPoint &startPoint, const QPoint &endPoint)
{
	QPainter painter(&image);
	painter.setPen(QPen(dColour, dDiameter, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(startPoint, endPoint);
	modified = true;
	
	int rad = (myPenWidth / 2) + 2;
	update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
	lastPoint = endPoint;
}
