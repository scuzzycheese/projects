#include "cNetwork.h"

cNetwork::cNetwork()
{
	//Set up the TCP server
	server = new cServer(0, &dClients);
}

cNetwork::~cNetwork()
{
	//cleanup
	delete server;
}
