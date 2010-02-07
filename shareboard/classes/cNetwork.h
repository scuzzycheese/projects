#ifndef CNETWORK_H
#define CNETWORK_H

#include <Qt/QtNetwork>
#include <QtGui/QLineEdit>
#include <QtGui/QDialog>
#include <QObject>

#define SERVERPORT 1234
#define SERVERBIND QHostAddress::Any

struct sNetPeer
{

	enum CLASS
	{
		MASTER = 0,
		PEER = 1,
		UNKNOWN = 3
	};

	enum STATUS
	{
		DEAD = 0,
		LIVE = 1
	};

	sNetPeer(CLASS cls, STATUS status) : dPeerClass(cls), dStatus(status)
	{
		dClient = NULL;
		dPeerIPAddress = QHostAddress::Null;
		//This might need to be more dynamic in future
		dPeerPort = SERVERPORT;

		dClient = NULL;
		dPeerPort = 0;
	}

	QTcpSocket *dClient;
	std::string dPeerName;
	QHostAddress dPeerIPAddress;
	quint16 dPeerPort;
	uint8_t dPeerClass : 2;
	uint8_t dStatus : 2;
};

//This is a nasty way to solve a resolution problem.
#include "cServer.h"

class cServer;

class cNetwork : public QObject
{
	Q_OBJECT	

	private:
		QDialog *connectDialog;

	public:
		cNetwork();
		~cNetwork();

		int mConnectToHost(const QString &host, quint16 port);
		void mPeerList();

		cServer *dServer;
		std::list<sNetPeer *> dClients;

		void setConnectDialog(QDialog *connDiag);

	public slots:	
		void mHandleConnection();
		void connectTo();



};



#endif

