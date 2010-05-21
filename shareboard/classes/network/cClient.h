#ifndef CNETWORK_H
#define CNETWORK_H

#include <Qt/QtNetwork>
#include <QtGui/QLineEdit>
#include <QtGui/QDialog>
#include <QObject>
#include "sNetPeer.h"


class cClient : public QWidget
{
	Q_OBJECT	

	private:
		QDialog *connectDialog;

	public:
		cClient(QWidget *parent = 0);
		~cClient();

		int mConnectToHost(const QString &host, quint16 port);
		void mPeerList();

		sNetPeer *dServer;

		void setConnectDialog(QDialog *connDiag);

	public slots:	
		void mHandleConnection();
		void mConnectToHostSlot(const QString &host, quint16 port);




};



#endif

