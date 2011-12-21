/* 
 * File:   cSerialTalk.cpp
 * Author: scuzzy
 * 
 * Created on 01 July 2011, 10:18 AM
 */

#include "cSerialTalk.h"

#include <stdio.h>

#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */


cSerialTalk::cSerialTalk(std::string dev) : device(dev)
{
	connect();
}


bool cSerialTalk::connect()
{
	std::cout << "connecting serial port" << std::endl;
	fdSerialPort = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if(fdSerialPort == -1)
	{
		std::cout << "Unable to open serial port " << device << std::endl;
		return false;
	}
	else
	{
		fcntl(fdSerialPort, F_SETFL, 0);
	}
	return true;
}

void cSerialTalk::disconnect()
{
	close(fdSerialPort);
	std::cout << "disconnecting serial port" << std::endl;
}

int cSerialTalk::write(char *data, int dataLen)
{
	return ::write(fdSerialPort, data, dataLen);
}

int cSerialTalk::read(char *data, int dataLen)
{
	return ::read(fdSerialPort, data, dataLen);
}

/*
cSerialTalk::cSerialTalk(const cSerialTalk& orig)
{
}
 */

cSerialTalk::~cSerialTalk()
{
	close(fdSerialPort);
}

