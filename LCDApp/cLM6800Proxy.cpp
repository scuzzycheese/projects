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

cLM6800Proxy::cLM6800Proxy(const cLM6800Proxy& orig)
{
}




void cLM6800Proxy::getPixel(uint8_t x, uint8_t y, union pixelColour *colour)
{

}
void cLM6800Proxy::setPixel(uint8_t x, uint8_t y)
{

}
void cLM6800Proxy::clearPixel(uint8_t x, uint8_t y)
{

}

void cLM6800Proxy::writeBlock(uint8_t x, uint8_t y, char *data)
{

}

struct lcdData cLM6800Proxy::getLcdData(void)
{

}
void cLM6800Proxy::init(void)
{
	lcdPort.write("", 4);
}
void cLM6800Proxy::reset(void)
{

}
void cLM6800Proxy::clearScreen(void)
{

}

cLM6800Proxy::~cLM6800Proxy()
{
}

