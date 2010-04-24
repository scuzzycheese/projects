#include "cServer.h"

/**
 * All clients start off as masters. The idea, is when
 * you opt to connect to another server you become a peer
 */
cServer::cServer(QWidget *parent) : QWidget(parent)
{

	dTcpSrv = new QTcpServer(parent);
	if(!dTcpSrv->listen(SERVERBIND, SERVERPORT))
	{
		printf("Error setting up server\n");
		//Do some error stuff here
		close();
		return;
	}
	printf("Server up and running\n");

	QObject::connect(dTcpSrv, SIGNAL(newConnection()), this, SLOT(mAcceptConnection()));
}

cServer::~cServer()
{
	for(std::list<sNetPeer *>::iterator item = dClients.begin(), end = dClients.end(); item != end; ++ item)
	{
		delete *item;
	}
}

void cServer::mAcceptConnection()
{
	printf("Connection Accepted\n");

	//Add peers to our list
	sNetPeer *peer = new sNetPeer(sNetPeer::CLIENT, sNetPeer::LIVE);
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
	QObject::connect(peer->dClient, SIGNAL(disconnected()), peer->dClient, SLOT(deleteLater()));

	peer->dClient->write("Hello from shareboard\r\n", 23);

	//finally push the peer onto the stack
	dClients.push_front(peer);
}





