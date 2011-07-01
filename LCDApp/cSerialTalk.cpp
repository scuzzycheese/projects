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


cSerialTalk::cSerialTalk()
{
	fdSerialPort = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	if(fdSerialPort == -1)
	{
		std::cout << "Unable to open serial port";
	}
	else
	{
		fcntl(fdSerialPort, F_SETFL, 0);
	}
}

int cSerialTalk::write(char *data, int dataLen)
{
	return ::write(fdSerialPort, data, dataLen);
}

int cSerialTalk::read(char *data, int dataLen)
{
	return ::read(fdSerialPort, data, dataLen);
}

cSerialTalk::cSerialTalk(const cSerialTalk& orig)
{
}

cSerialTalk::~cSerialTalk()
{
	close(fdSerialPort);
}

