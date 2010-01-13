#ifndef CNETWORK_H
#define CNETWORK_H

#include <Qt/QtNetwork>

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

class cNetwork
{
	
	public:
		cNetwork();
		~cNetwork();

		cServer *server;
		std::list<sNetPeer *> dClients;

};



#endif

