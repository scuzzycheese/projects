#ifndef _CLCDDOCKWIDGET_H
#define	_CLCDDOCKWIDGET_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QLCDNumber>
#include <QEvent>

class cLCDDockWidget : public QLCDNumber
{
	Q_OBJECT
public:
	cLCDDockWidget(QWidget *parent = 0);
	virtual ~cLCDDockWidget();
	//bool event(QEvent *e);
private:
	QImage dImage;
protected:
	void resizeEvent(QResizeEvent *event);
signals:
	void sizeChanged(int x, int y);


};

#endif	/* _CLCDDOCKWIDGET_H */

