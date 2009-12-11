#include "cServer.h"

cServer::cServer(QWidget *parent) : QWidget(parent)
{

	dTcpSrv = new QTcpServer(this);
	if(!dTcpSrv->listen(SERVERBIND, SERVERPORT))
	{
		printf("Error setting up server\n");
		//Do some error stuff here
		close();
		return;
	}
	printf("Server up and running\n");

	connect(dTcpSrv, SIGNAL(newConnection()), this, SLOT(mAcceptConnection()));

}

void cServer::mAcceptConnection()
{
	printf("Connection Accepted\n");

	QTcpSocket *client = dTcpSrv->nextPendingConnection();
	
	//I presume this is just a nice cleanup routine
	connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));


	client->write("Hello\r\n", 7);
	client->disconnectFromHost();

}
