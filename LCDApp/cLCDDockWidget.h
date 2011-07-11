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
	void resizeImage(QImage *image, const QSize &newSize);
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

};

#endif	/* _CLCDDOCKWIDGET_H */

