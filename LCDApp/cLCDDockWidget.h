#ifndef _CLCDDOCKWIDGET_H
#define	_CLCDDOCKWIDGET_H

#include <QWidget>
#include <QColor>
#include <QImage>

class cLCDDockWidget : public QWidget
{
	Q_OBJECT
public:
	cLCDDockWidget(QWidget *parent = 0);
	virtual ~cLCDDockWidget();
private:
	QImage dImage;
protected:
	void paintEvent(QPaintEvent *event);

};

#endif	/* _CLCDDOCKWIDGET_H */

