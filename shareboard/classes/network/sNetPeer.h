#include <iostream>
#include <QObject>
#include <Qt/QtNetwork>
#include <stdint.h>

#ifndef _SNETPEER_H
#define	_SNETPEER_H

class sNetPeer : public QObject
{
	Q_OBJECT

public:
	enum CLASS
	{
		CLIENT,
		UNKNOWN
	};

	enum STATUS
	{
		DEAD,
		LIVE
	};

	sNetPeer(CLASS cls, STATUS status, QTcpSocket *sock, QObject *parent = 0) : QObject(parent), dPeerClass(cls), dStatus(status), dClient(sock)
	{
		dPeerIPAddress = QHostAddress::Null;
		dPeerPort = 0;
		QObject::connect(dClient, SIGNAL(readyRead()), this, SLOT(mHandleDataReady()));
	}

	~sNetPeer()
	{

	}

	std::string dPeerName;
	QHostAddress dPeerIPAddress;
	quint16 dPeerPort;
	uint8_t dPeerClass : 2;
	uint8_t dStatus : 2;
	QTcpSocket *dClient;


signals:
	void sDataReady();

public slots:
	void mHandleDataReady()
	{
		emit(sDataReady());
	}

};


#endif	/* _SNETPEER_H */

