/* 
 * File:   cPlugin.cpp
 * Author: scuzzy
 * 
 * Created on 01 December 2011, 4:34 PM
 */

#include "cPlugin.h"
#include "cPluginHandler.h"




cPlugin::cPlugin() : 
	gfxBuff(NULL),
	maxX(0),
	maxY(0),
	startX(0),
	startY(0)
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

void cPlugin::flushNow()
{
	cMessage mess;
	mess.setMessageType(cMessage::MESSAGE_FLUSH);
	queue->enqueue(mess);
}

void cPlugin::setQueue(cQueue *q)
{
	queue = q;
}

cPlugin::~cPlugin()
{
}

