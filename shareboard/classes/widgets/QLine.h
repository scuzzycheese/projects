#ifndef QLINE_H
#define QLINE_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QImage>
#include <iostream>
#include <deque>

using namespace std;

class QLine : public QObject
{
	Q_OBJECT

	private:
		deque<QPoint> *dLine;
		QColor dColour;
		int dDiameter;

		void drawLine(QImage &image, const QPoint &startPoint, const QPoint &endPoint);

	public:
		QLine();
		QLine(QColor colour, int diameter);
		~QLine();

};

#endif
