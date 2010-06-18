#include "cClient.h"

cClient::cClient(QWidget *parent) : QWidget(parent)
{
	dServer = NULL;
}

/**
 * NOTE: not tested yet
 */
cClient::~cClient()
{
	printf("Cleaning up!\n");
	delete(dServer);
}


/**
 * NOTE: not tested yet
 */
int cClient::mConnectToHost(const QString &host, quint16 port)
{
	QTcpSocket *sock = new QTcpSocket();
	sock->connectToHost(host, port, QIODevice::ReadWrite);
	sock->waitForConnected(1000);

	dServer = new sNetPeer(sNetPeer::CLIENT, sNetPeer::LIVE, sock);
	dServer->dPeerIPAddress = sock->peerAddress();
	dServer->dPeerPort = port;

	//Some cleanup mastery from QT
	QObject::connect(sock, SIGNAL(disconnected()), sock, SLOT(deleteLater()));

	//Tryin to connect this signal to the handler below, without much sucess.
	//TODO: see if it works
	QObject::connect(sock, SIGNAL(connected()), this, SLOT(mHandleConnection()));

	return 0;
}
void cClient::mConnectToHostSlot(const QString &host, quint16 port)
{
	mConnectToHost(host, port);
}

void cClient::mHandleConnection()
{
	printf("Connection Complete\n");
}