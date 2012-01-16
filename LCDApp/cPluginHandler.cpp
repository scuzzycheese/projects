/* 
 * File:   cPluginHandler.cpp
 * Author: scuzzy
 * 
 * Created on 01 December 2011, 3:29 PM
 */

#include "cPluginHandler.h"
#include <iostream>


cPluginHandler::cPluginHandler() :
	proxy(NULL)
{
	memset((char *)gfxBuffer, 0x00, 2048);
	memset((char *)CRC, 0x00, 64);
	//instantiate a new queue for us to use
	queue = new cQueue;
}

cPluginHandler::~cPluginHandler()
{
	delete(queue);
}


//Adding the plugins to the lists maybe needs to be handled outside this class.
//Haven't figured this one out yet
void cPluginHandler::addPlugin(cPlugin *(*pluginFactory)(), std::string name)
{
	//maintain a list of plugins in memory
	pluginList[name] = pluginFactory;
}

void cPluginHandler::setPluginActive(cPlugin *plugin)
{
	//maintain a list of active plugins
	activePlugins[plugin->getName()] = plugin;

	//set some fake limits for the plugin
	//plugin->maxX = 256;
	//plugin->maxY = 64;

	plugin->gfxBuff = (char *)gfxBuffer;
	plugin->setQueue(queue);

	plugin->start();
}

void cPluginHandler::setProxy(cLM6800Proxy *proxy)
{
	this->proxy = proxy;
}

uint16_t cPluginHandler::crc16(uint16_t crc, uint8_t a)
{
	int i;

	crc ^= a;
	for(i = 0; i < 8; ++i)
	{
		if(crc & 1) crc = (crc >> 1) ^ 0xA001;
		else crc = (crc >> 1);
	}
	return crc;
}

void cPluginHandler::flush()
{
	for(int x = 0; x < 4; x ++)
	{
		for(int y = 0; y < 8; y ++)
		{
			uint16_t pageCRC = 0;
			for(int z = 0; z < 64; z ++)
			{
				pageCRC = crc16(pageCRC, gfxBuffer[x][y][z]);
			}
			if(CRC[x][y] != pageCRC)
			{
				//std::cout << "Writing Block: X - " << x << " Y - " << y << std::endl;
				proxy->writeBlock(x, y, gfxBuffer[x][y]);
				CRC[x][y] = pageCRC;
			}
		}
	}

}

void cPluginHandler::cleanBuffer()
{
	memset((char *)gfxBuffer, 0x00, 2048);
}



/*
 * TODO: This has concurancy issues
 */
void cPluginHandler::run()
{
	//std::cout << "Starting Plugin Handler" << std::endl;
	//activate plugins
	//NOTE:THIS CODE DOESN'T DO ANYTHING YET
	std::map<std::string, cPlugin *>::iterator activePlugin;
	for(activePlugin = activePlugins.begin(); activePlugin != activePlugins.end(); activePlugin ++)
	{
		//std::cout << "starting plugin" << activePlugin->first << std::endl;
		activePlugin->second->start();
	}




	while(1)
	{
		cMessage mess;
		queue->dequeue(mess);

		switch(mess.getMessageType())
		{
			case cMessage::MESSAGE_FLUSH:
			{
				flush();
				break;
			}
			case cMessage::MESSAGE_CLR_BUFFER:
			{
				cleanBuffer();
				break;
			}
		}
	}
}

//NOTE: this is explicitly linked to an outside QWidget...
cPlugin *cPluginHandler::addPluginInstance(std::string pluginName)
{
	cPlugin *(*pluginFactory)() = pluginList[pluginName];
	cPlugin *plugin = NULL;
	if(pluginFactory)
	{
		plugin = pluginFactory();
	}

	if(plugin)
	{
		setPluginActive(plugin);
	}
	return plugin;
}