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

	//We push ourselves onto the peer list
	sNetPeer peer(sNetPeer::MASTER, sNetPeer::LIVE);
	dClients.push_front(peer);
	

}

void cServer::mAcceptConnection()
{
	

	printf("Connection Accepted\n");

	//Add peers to our list
	sNetPeer peer(sNetPeer::PEER, sNetPeer::LIVE);
	peer.dClient = dTcpSrv->nextPendingConnection();

	//Add some additional information
	peer.dHostAddress = peer.dClient->peerAddress();
	//We just adopt OUR bind port, in future I want the host
	//to be able to announce what port peers must connect to 
	//it on.
	peer.dHostPort = peer.dClient->localPort();

	dClients.push_front(peer);
	
	//I presume this is just a nice cleanup routine
	connect(peer.dClient, SIGNAL(disconnected()), peer.dClient, SLOT(deleteLater()));


	peer.dClient->write("Hello from shareboard\r\n", 23);
	//client->disconnectFromHost();

}



