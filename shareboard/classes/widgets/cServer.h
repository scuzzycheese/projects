#ifndef CSERVER_H
#define CSERVER_H


#include <Qt/QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QWidget>
#include <deque>
#include "sNetPeer.h"
#include "cPDU.h"
#include <iostream>

#define SERVERBIND QHostAddress::Any
#define SERVERPORT 1234

class cServer : public QWidget
{
	Q_OBJECT

	private:
		QTcpServer *dTcpSrv;
		QString serverName;

	public:
		std::list<sNetPeer *> dClients;
		cServer(QString srvName, QWidget *parent = 0);
		~cServer();
		void mRelayMessage(cPDU &message);
		void mSendToHost(QTcpSocket *sock, cPDU &message);
		static char *mGetPDUFromSocket(QTcpSocket *sock);
		static bool mSendPDUToSocket(QTcpSocket *sock, cPDU &pdu);



	public slots:
		void mAcceptConnection();
		void mHandleData();


};


#endif
