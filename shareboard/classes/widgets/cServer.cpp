#include "cServer.h"

cServer::cServer(QWidget *parent) : QWidget(parent), dSelfPeer(sNetPeer::UNKNOWN, sNetPeer::LIVE)
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
	dClients.push_front(&dSelfPeer);

}

cServer::~cServer()
{
	//clean up all the memory we used
	for(std::list<sNetPeer *>::iterator sNetPeerIter = dClients.begin(); sNetPeerIter != dClients.end(); sNetPeerIter ++)
	{
		sNetPeer *peer = *sNetPeerIter;
		delete(peer);
	}
}

void cServer::mAcceptConnection()
{
	printf("Connection Accepted\n");

	//Add peers to our list
	sNetPeer *peer = new sNetPeer(sNetPeer::PEER, sNetPeer::LIVE);
	peer->dClient = dTcpSrv->nextPendingConnection();

	//Add some additional information
	peer->dPeerIPAddress = peer->dClient->peerAddress();
	//We just adopt OUR bind port, in future I want the host
	//to be able to announce what port peers must connect to 
	//it on.
	peer->dPeerPort = SERVERPORT;

	
	//I presume this is just a nice cleanup routine
	connect(peer->dClient, SIGNAL(disconnected()), peer->dClient, SLOT(deleteLater()));


	peer->dClient->write("Hello from shareboard\r\n", 23);

	//since I don't know what interface clients are binding to,
	//I need to find out on my first inward connection
	if(dSelfPeer.dPeerIPAddress == QHostAddress::Null)
	{
		dSelfPeer.dPeerIPAddress = peer->dClient->localAddress();
	}


	//finally push the peer onto the stack
	dClients.push_front(peer);
}





