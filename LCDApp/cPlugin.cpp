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
	master(NULL),
	maxX(0),
	maxY(0),
	startX(0),
	startY(0)
{
}

std::string cPlugin::getName()
{
	return pluginName;
}

void cPlugin::setName(const std::string &name)
{
	pluginName = name;
}

void cPlugin::setPixel(int x, int y)
{
	x += startX;
	y += startY;
	if(x >= 0 && x <= maxX && y >= 0 && y <= maxY)
	{
		//gfxBuff[y * bufXVal + (x >> 3)] |= (1 << (7 - (x & 7)));
		gfxBuff[((y >> 3) * 7 + (x >> 6)) + (x & 63)] |= (1 << (y & 7));
	}
}

void cPlugin::clearPixel(int x, int y)
{
	x += startX;
	y += startY;
	if(x >= 0 && x <= maxX && y >= 0 && y <= maxY)
	{
		//gfxBuff[y * bufXVal + (x >> 3)] &= ~(1 << (7 - (x & 7)));
		gfxBuff[((y >> 3) * 7 + (x >> 6)) + (x & 63)] &= ~(1 << (y & 7));
	}
}

void cPlugin::flushNow()
{
	master->incFlushFlag();
}

cPlugin::cPlugin(const cPlugin& orig)
{
}

cPlugin::~cPlugin()
{
}

