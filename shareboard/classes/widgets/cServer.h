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
		PEER = 1
	};

	enum STATUS
	{
		DEAD = 0,
		LIVE = 1
	};

	sNetPeer(CLASS cls, STATUS status) : dPeerClass(cls), dStatus(status)
	{
		dClient = NULL;
		dHostAddress = QHostAddress::Null;
	}

	QTcpSocket *dClient;
	std::string dPeerName;
	QHostAddress dHostAddress;
	quint16 dHostPort;
	uint8_t dPeerClass : 2;
	uint8_t dStatus : 2;
};

class cServer : public QWidget
{
	Q_OBJECT

	private:
		QTcpServer *dTcpSrv;
		std::deque<sNetPeer> dClients;

	public:
		cServer(QWidget *parent = 0);

	public slots:
		void mAcceptConnection();


};


#endif
