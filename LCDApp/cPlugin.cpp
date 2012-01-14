/* 
 * File:   cPlugin.cpp
 * Author: scuzzy
 * 
 * Created on 01 December 2011, 4:34 PM
 */

#include "cPlugin.h"
#include "cPluginHandler.h"




cPlugin::cPlugin() :
	width(0),
	height(0),
	maxX(0),
	maxY(0),
	startX(0),
	startY(0),
	gfxBuff(NULL)
{
}

std::string cPlugin::getName()
{
	return pluginName;
}

void cPlugin::setName(std::string name)
{
	pluginName = name;
}

void cPlugin::setPixel(int x, int y)
{
	x += startX;
	y += startY;
	if(x >= startX && x <= maxX && y >= startY && y <= maxY)
	{
/*
		int Py = y >> 3;
		int PX = 64;
		int PY = 512;
		int Px = x >> 6;

		int X = x & 63;
		int Y = y & 7;

		int res = (Px * PY) + (Py * PX) + X;

		gfxBuff[res] |= (1 << (Y));
 */

		gfxBuff[((x >> 6) * 512) + ((y >> 3) * 64) + (x & 63)] |= (1 << (y & 7));
	}
}

void cPlugin::clearPixel(int x, int y)
{
	x += startX;
	y += startY;
	if(x >= startX && x <= maxX && y >= startY && y <= maxY)
	{
		gfxBuff[((x >> 6) * 512) + ((y >> 3) * 64) + (x & 63)] &= ~(1 << (y & 7));
	}
}

//TODO: Optimise
void cPlugin::clrScreen()
{
	for(int x = 0; x < width; ++ x)
	{
		for(int y = 0; y < height; ++y)
		{
			clearPixel(x, y);
		}
	}
}

void cPlugin::flushNow()
{
	//std::cout << "cPlugin flushing buffer now" << std::endl;
	cMessage mess;
	mess.setMessageType(cMessage::MESSAGE_FLUSH);
	queue->enqueue(mess);
}

void cPlugin::setQueue(cQueue *q)
{
	queue = q;
}

void cPlugin::setMaxX(int x)
{
	maxX = (x <= 255) ? x : 255;
	std::cout << "maxX: " << maxX << std::endl;
}
void cPlugin::setMaxY(int y)
{
	maxY = (y <= 63) ? y : 63;
	std::cout << "maxY: " << maxY << std::endl;
}
void cPlugin::setStartX(int x)
{
	startX = x;
	std::cout << "startX: " << x << std::endl;
}
void cPlugin::setStartY(int y)
{
	startY = y;
	std::cout << "startY: " << y << std::endl;
}

void cPlugin::setWidth(int x)
{
	width = x;
}

void cPlugin::setHeight(int y)
{
	height = y;
}

cPlugin::~cPlugin()
{
}

