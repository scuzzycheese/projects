#ifndef CCONNDIAGH
#define CCONNDIAGH

#include <QtGui/QDialog>
#include <QObject>
#include <QWidget>
#include "ui_connectDialog.h"
#include "cServer.h"

namespace Ui
{
	class cConnDiag;
}

class cConnDiag : public QDialog
{
	Q_OBJECT

public:
	cConnDiag(QWidget *parent = 0);

private:
	Ui::ConnectDialog *cd;

public slots:
	void mHandleConnectButton();

signals:
	void connectToHost(const QString &host, quint16 port);





};


#endif
