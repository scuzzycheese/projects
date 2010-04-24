#ifndef CSERVER_H
#define CSERVER_H


#include <Qt/QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QWidget>
#include <deque>
#include "sNetPeer.h"

#define SERVERBIND QHostAddress::Any
#define SERVERPORT 1234

class cServer : public QWidget
{
	Q_OBJECT

	private:
		QTcpServer *dTcpSrv;

	public:
		std::list<sNetPeer *> dClients;
		cServer(QWidget *parent = 0);
		~cServer();

	public slots:
		void mAcceptConnection();


};


#endif
