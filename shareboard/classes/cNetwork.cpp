#include "cNetwork.h"

cNetwork::cNetwork()
{
	connectDialog = NULL;

	//Set up the TCP server
	dServer = new cServer(0, &dClients);
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
	delete dServer;
}


/**
 * NOTE: not tested yet
 */
int cNetwork::mConnectToHost(const QString &host, quint16 port)
{
	QTcpSocket *sock = new QTcpSocket();
	sock->connectToHost(host, port, QIODevice::ReadWrite);
	sock->waitForConnected(1000);

	sNetPeer *peer = new sNetPeer(sNetPeer::PEER, sNetPeer::LIVE);
	peer->dClient = sock;
	peer->dPeerIPAddress = peer->dClient->peerAddress();
	peer->dPeerPort = port;

	//Some cleanup mastery from QT
	QObject::connect(peer->dClient, SIGNAL(disconnected()), peer->dClient, SLOT(deleteLater()));

	//Tryin to connect this signal to the handler below, without much sucess.
	//TODO: see if it works
	QObject::connect(peer->dClient, SIGNAL(connected()), this, SLOT(mHandleConnection()));

	dClients.push_front(peer);

	return 0;
}

void cNetwork::mHandleConnection()
{

	printf("Connection Complete\n");

}

/**
 * purely for debugging at this stage
 */
void cNetwork::mPeerList()
{

	for(std::list<sNetPeer *>::iterator sNetPeerIter = dClients.begin(); sNetPeerIter != dClients.end(); sNetPeerIter ++)
	{
		if((*sNetPeerIter)->dPeerIPAddress.isNull())
		{
			printf("Found NULL address\n");
		}
		printf("HOST: %s\n", qPrintable((*sNetPeerIter)->dPeerIPAddress.toString()));
		printf("PORT: %d\n", (*sNetPeerIter)->dPeerPort);
		printf("CLASS: %d\n", (*sNetPeerIter)->dPeerClass);
		printf("STATUS: %d\n\n", (*sNetPeerIter)->dStatus);
	}


}



void cNetwork::connectTo()
{
	QLineEdit *hostLine = connectDialog->findChild<QLineEdit *>("host");

	mConnectToHost(hostLine->text(), SERVERPORT);

	//printf("HIT: %s\n", hostLine->text().toLocal8Bit().data());
	connectDialog->hide();
}

void cNetwork::setConnectDialog(QDialog *connDiag)
{
	connectDialog = connDiag;
}

