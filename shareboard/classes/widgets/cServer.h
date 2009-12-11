#ifndef CSERVER_H
#define CSERVER_H

#include <QtNetwork>

class cServer
{

	private:
		QTcpServer *cTcpSrv;

	public:
		cServer(int port);


};


#endif
