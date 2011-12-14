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

QString cPlugin::getName()
{
	return pluginName;
}

void cPlugin::setName(QString name)
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
	std::cout << "cPlugin flushing buffer now" << std::endl;
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
	std::cout << "maxX: " << x << std::endl;
	maxX = x;
}
void cPlugin::setMaxY(int y)
{
	std::cout << "maxY: " << y << std::endl;
	maxY = y;
}
void cPlugin::setStartX(int x)
{
	std::cout << "startX: " << x << std::endl;
	startX =x;
}
void cPlugin::setStartY(int y)
{
	std::cout << "startY: " << y << std::endl;
	startY = y;
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

