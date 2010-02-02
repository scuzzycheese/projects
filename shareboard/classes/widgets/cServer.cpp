#include "cServer.h"

/**
 * All clients start off as masters. The idea, is when
 * you opt to connect to another server you become a peer
 */
cServer::cServer(QWidget *parent, std::list<sNetPeer *> *clients) : QWidget(parent), dSelfPeer(sNetPeer::MASTER, sNetPeer::LIVE), dClients(clients)
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
	dClients->push_front(&dSelfPeer);

}

/**
 * Even tho we populate a large chunk of the dClients list, 
 * we don't actuall own it, we just write to it, so the
 * cleanup must be handled buy the server class, not this
 * one
 */
cServer::~cServer()
{
}

void cServer::mAcceptConnection()
{
	printf("Connection Accepted\n");

	//Add peers to our list
	sNetPeer *peer = new sNetPeer(sNetPeer::PEER, sNetPeer::LIVE);
	peer->dClient = dTcpSrv->nextPendingConnection();
	//I don't even know if this is nessesary in this slot
	peer->dClient->waitForConnected(1000);

	//Add some additional information
	peer->dPeerIPAddress = peer->dClient->peerAddress();
	//We just adopt OUR bind port, in future I want the host
	//to be able to announce what port peers must connect to 
	//it on.
	peer->dPeerPort = SERVERPORT;

	
	//I presume this is just a nice cleanup routine
	connect(peer->dClient, SIGNAL(disconnected()), peer->dClient, SLOT(deleteLater()));



	//since I don't know what interface clients are binding to,
	//I need to find out on my first inward connection
	if(dSelfPeer.dPeerIPAddress == QHostAddress::Null)
	{
		dSelfPeer.dPeerIPAddress = peer->dClient->localAddress();
	}

	peer->dClient->write("Hello from shareboard\r\n", 23);

	//finally push the peer onto the stack
	dClients->push_front(peer);
}





