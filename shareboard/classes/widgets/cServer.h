#ifndef CSERVER_H
#define CSERVER_H


#define SERVERPORT 1234
#define SERVERBIND QHostAddress::Any


#include <Qt/QtNetwork>
#include <QWidget>
#include <deque>


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

class cServer : public QWidget
{
	Q_OBJECT

	private:
		QTcpServer *dTcpSrv;
		std::list<sNetPeer *> dClients;
		sNetPeer dSelfPeer;

	public:
		cServer(QWidget *parent = 0);
		~cServer();

	public slots:
		void mAcceptConnection();


};


#endif
