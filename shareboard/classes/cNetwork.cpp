#include "cNetwork.h"

cNetwork::cNetwork()
{
	//Set up the TCP server
	server = new cServer(0, &dClients);
}

/**
 * NOTE: not tested yet
 */
cNetwork::~cNetwork()
{
	printf("Cleaning up!\n");
	//clean up all the memory we used
	for(std::list<sNetPeer *>::iterator sNetPeerIter = dClients.begin(); sNetPeerIter != dClients.end(); sNetPeerIter ++)
	{
		sNetPeer *peer = *sNetPeerIter;
		delete(peer);
	}
	printf("Done\n");

	//cleanup
	delete server;
}


/**
 * NOTE: not tested yet
 */
int cNetwork::connectToHost(const QString &host, quint16 port)
{
	QTcpSocket *sock = new QTcpSocket();
	sock->connectToHost(host, port, QIODevice::ReadWrite);

	sNetPeer *peer = new sNetPeer(sNetPeer::PEER, sNetPeer::LIVE);
	peer->dClient = sock;
	peer->dPeerIPAddress = peer->dClient->peerAddress();
	peer->dPeerPort = port;

	//Some cleanup mastery from QT
	QObject::connect(peer->dClient, SIGNAL(disconnected()), peer->dClient, SLOT(deleteLater()));

	dClients.push_front(peer);

	return 0;
}
