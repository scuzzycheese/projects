/* 
 * File:   cSerialTalk.h
 * Author: scuzzy
 *
 * Created on 01 July 2011, 10:18 AM
 */

#ifndef _CSERIALTALK_H
#define	_CSERIALTALK_H

#include <iostream>

class cSerialTalk
{
public:
	cSerialTalk(std::string dev);
	//cSerialTalk(const cSerialTalk& orig);
	bool connect();
	void disconnect();
	int write(char *data, int dataLen);
	int read(char *data, int dataLen);
	virtual ~ cSerialTalk();
private:
	int fdSerialPort;
	std::string device;

};

#endif	/* _CSERIALTALK_H */

