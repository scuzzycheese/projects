/* 
 * File:   cStartServerDiag.h
 * Author: scuzzy
 *
 * Created on 27 April 2010, 23:19
 */

#ifndef _CSTARTSERVERDIAG_H
#define	_CSTARTSERVERDIAG_H

#include <QtGui/QDialog>
#include <QObject>
#include <QWidget>
#include "ui_startNetworkDialog.h"

namespace Ui
{
	class cStartServerDiag;
}

class cStartServerDiag : public QDialog
{
	Q_OBJECT

public:
	cStartServerDiag(QWidget *parent = 0);

private:
	Ui::StartNetworkDialog *ssd;

public slots:
	void mHandleServerStartButton();

signals:
	void connectToHost(const QString &host, quint16 port);





};



#endif	/* _CSTARTSERVERDIAG_H */

