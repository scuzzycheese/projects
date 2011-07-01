/* 
 * File:   cLM6800Proxy.h
 * Author: scuzzy
 *
 * Created on 01 July 2011, 11:08 PM
 */

#ifndef _CLM6800PROXY_H
#define	_CLM6800PROXY_H

#include <inttypes.h>

#define BITDEPTH 1

#include "lcdFramework.h"
#include "cSerialTalk.h"

/**
 *	BINARY PROTOCOL BETWEEN LCD AND CLIENT
 *
 * first Byte:
 *
 *
 *
 */


class cLM6800Proxy
{
public:

	void getPixel(uint8_t x, uint8_t y, union pixelColour *colour);
	void setPixel(uint8_t x, uint8_t y);
	void clearPixel(uint8_t x, uint8_t y);

	void writeBlock(uint8_t x, uint8_t y, char *data);

	struct lcdData getLcdData(void);
	void init(void);
	void reset(void);
	void clearScreen(void);


	cLM6800Proxy();
	cLM6800Proxy(const cLM6800Proxy& orig);
	virtual ~ cLM6800Proxy();
private:

	cSerialTalk lcdPort;

};

#endif	/* _CLM6800PROXY_H */

