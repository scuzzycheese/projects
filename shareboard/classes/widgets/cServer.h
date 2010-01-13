#ifndef CSERVER_H
#define CSERVER_H


#include <Qt/QtNetwork>
#include <QWidget>
#include <deque>
#include "cNetwork.h"

class cServer : public QWidget
{
	Q_OBJECT

	private:
		QTcpServer *dTcpSrv;
		sNetPeer dSelfPeer;

	public:
		std::list<sNetPeer *> *dClients;
		cServer(QWidget *parent = 0, std::list<sNetPeer *> *clients = NULL);
		~cServer();

	public slots:
		void mAcceptConnection();


};


#endif
