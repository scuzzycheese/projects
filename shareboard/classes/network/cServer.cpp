#include "cServer.h"

/**
 * All clients start off as masters. The idea, is when
 * you opt to connect to another server you become a peer
 */
cServer::cServer(QString srvName, QWidget *parent) : QWidget(parent), serverName(srvName)
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
	sNetPeer *peer = new sNetPeer(sNetPeer::CLIENT, sNetPeer::LIVE, dTcpSrv->nextPendingConnection());
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
	//Handle incomming data
	QObject::connect(peer, SIGNAL(sDataReady()), this, SLOT(mHandleData()));

	peer->dClient->write("Hello from shareboard\r\n", 23);

	//finally push the peer onto the stack
	dClients.push_front(peer);
}

void cServer::mHandleData()
{
	//aquire a pointer to the sender of the signal, in this case sNetPeer
	sNetPeer *client = (sNetPeer *)sender();
	std::cout << "DATA: " << client->dClient->readAll().constData() << std::endl;
}


void cServer::mRelayMessage(cPDU &message)
{
	for(std::list<sNetPeer *>::iterator item = dClients.begin(), end = dClients.end(); item != end; ++ item)
	{
		mSendToHost((*item)->dClient, message);
	}
}

void cServer::mSendToHost(QTcpSocket *sock, cPDU &message)
{
	mSendPDUToSocket(sock, message);
}


/**
 * Old Nasty static methods to help us out
 */

char *cServer::mGetPDUFromSocket(QTcpSocket *sock)
{
   m_int32 length;

	sock->read((char *)&length, sizeof(length));

   char *dta = new char[length];
   memcpy(dta, &length, sizeof(length));

	sock->read((char *)dta + sizeof(length), length - sizeof(length));
   return dta;
}

bool cServer::mSendPDUToSocket(QTcpSocket *sock, cPDU &pdu)
{
   m_int32 res = sock->write((const char *)pdu.mGetPDU(), pdu.mGetPDULength());
   if(res == -1)
   {
      std::cout << "send() failed with error: " <<  sock->errorString().toStdString() << std::endl;
      return false;
   }
   return true;
}