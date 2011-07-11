/* 
 * File:   cDockMainWindow.h
 * Author: scuzzy
 *
 * Created on 08 July 2011, 11:04 PM
 */


#ifndef _CDOCKMAINWINDOW_H
#define	_CDOCKMAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QtGui>

class cDockMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	cDockMainWindow();
	cDockMainWindow(QMainWindow *parent);
	void createDock();
	virtual ~ cDockMainWindow();
private:
	QImage dImage;
protected:
	void mousePressEvent(QMouseEvent *event);

};

#endif	/* _CDOCKMAINWINDOW_H */

