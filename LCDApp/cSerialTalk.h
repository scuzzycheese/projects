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
	cSerialTalk();
	//cSerialTalk(const cSerialTalk& orig);
	int write(char *data, int dataLen);
	int read(char *data, int dataLen);
	virtual ~ cSerialTalk();
private:
	int fdSerialPort;

};

#endif	/* _CSERIALTALK_H */

