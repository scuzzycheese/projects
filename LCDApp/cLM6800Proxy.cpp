/* 
 * File:   cLM6800Proxy.cpp
 * Author: scuzzy
 * 
 * Created on 01 July 2011, 11:08 PM
 */

#include "cLM6800Proxy.h"

cLM6800Proxy::cLM6800Proxy()
{
	init();
}

cLM6800Proxy::cLM6800Proxy(cSerialTalk *lcdPoObj) : lcdPort(lcdPoObj)
{
}

cLM6800Proxy::cLM6800Proxy(const cLM6800Proxy& orig)
{
}

void cLM6800Proxy::setLcdPort(cSerialTalk *lcdPoObj)
{
	lcdPort = lcdPoObj;
}


void cLM6800Proxy::getPixel(uint8_t x, uint8_t y, union pixelColour *colour)
{
	char tmpWriter[3];
	tmpWriter[0] = 0b10000000;
	tmpWriter[1] = x;
	tmpWriter[2] = y;
	lcdPort->write(tmpWriter, 3);

	lcdPort->read((char *)colour, sizeof(union pixelColour));
}
void cLM6800Proxy::setPixel(uint8_t x, uint8_t y)
{
	char tmpWriter[3];
	tmpWriter[0] = 0b01000000;
	tmpWriter[1] = x;
	tmpWriter[2] = y;
	lcdPort->write(tmpWriter, 3);
}
void cLM6800Proxy::clearPixel(uint8_t x, uint8_t y)
{
	char tmpWriter[3];
	tmpWriter[0] = 0b01000001;
	tmpWriter[1] = x;
	tmpWriter[2] = y;
	lcdPort->write(tmpWriter, 3);
}

void cLM6800Proxy::writeBlock(uint8_t x, uint8_t y, char *data)
{
	char tmpWriter[3];
	tmpWriter[0] = 0b01000010;
	tmpWriter[1] = x;
	tmpWriter[2] = y;
	lcdPort->write(tmpWriter, 3);
	lcdPort->write(data, 64);
}

struct lcdData cLM6800Proxy::getLcdData(void)
{
	char tmpChar = 0b10000001;
	lcdPort->write(&tmpChar, 1);

	struct lcdData retData;
	lcdPort->read((char *)(&retData), sizeof(struct lcdData));
	return retData;
}
void cLM6800Proxy::init(void)
{
	char tmpChar = 0b00000000;
	lcdPort->write(&tmpChar, 1);
}
void cLM6800Proxy::reset(void)
{
	char tmpChar = 0b00000001;
	lcdPort->write(&tmpChar, 1);
}
void cLM6800Proxy::clearScreen(void)
{
	char tmpChar = 0b00000010;
	lcdPort->write(&tmpChar, 1);
}

cLM6800Proxy::~cLM6800Proxy()
{
}

