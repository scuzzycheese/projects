/* 
 * File:   sNetPeer.h
 * Author: scuzzy
 *
 * Created on 23 April 2010, 16:55
 */
#include <iostream>

#ifndef _SNETPEER_H
#define	_SNETPEER_H

struct sNetPeer
{

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

	sNetPeer(CLASS cls, STATUS status) : dPeerClass(cls), dStatus(status)
	{
		dClient = NULL;
		dPeerIPAddress = QHostAddress::Null;

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


#endif	/* _SNETPEER_H */

