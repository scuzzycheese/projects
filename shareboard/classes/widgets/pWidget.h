#ifndef PWIDGET_H
#define PWIDGET_H

#include <QWidget>
#include <QBrush>
#include <QFont>
#include <QPen>

class QPaintEvent;

class pWidget : public QWidget
{
	Q_OBJECT
	
	public:
		pWidget(QWidget *parent);
	
	public slots:
		void animate();
	
	protected:
		void paintEvent(QPaintEvent *event);
		void paint(QPainter *painter, QPaintEvent *event, int elapsed);
	
	private:
		int elapsed;


		//Painting stuff
		QBrush background;
		QBrush circleBrush;
		QFont textFont;
		QPen circlePen;
		QPen textPen;
};



#endif
