/* 
 * File:   cCustomDockTitle.h
 * Author: scuzzy
 *
 * Created on 31 August 2011, 4:52 PM
 */

#ifndef _CCUSTOMDOCKTITLE_H
#define	_CCUSTOMDOCKTITLE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QMoveEvent>
#include "cCustomDockWidget.h"

class cCustomDockTitle : public QWidget
{
public:
	cCustomDockTitle(QWidget *parent);
	virtual ~ cCustomDockTitle();
private:
	QWidget *parent;
	QPoint cursor;
	cCustomDockWidget *parentDockWidget;

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

#endif	/* _CCUSTOMDOCKTITLE_H */

