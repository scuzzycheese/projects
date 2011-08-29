#ifndef _CLCDDOCKWIDGET_H
#define	_CLCDDOCKWIDGET_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QLCDNumber>

class cLCDDockWidget : public QLCDNumber
{
	Q_OBJECT
public:
	cLCDDockWidget(QWidget *parent = 0);
	virtual ~cLCDDockWidget();
private:
	QImage dImage;
protected:
	void resizeEvent(QResizeEvent *event);

};

#endif	/* _CLCDDOCKWIDGET_H */

