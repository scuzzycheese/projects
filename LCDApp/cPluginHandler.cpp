/* 
 * File:   cPluginHandler.cpp
 * Author: scuzzy
 * 
 * Created on 01 December 2011, 3:29 PM
 */

#include "cPluginHandler.h"
#include <iostream>

cPluginHandler::cPluginHandler(QFrame *plgCnfFrm, QListWidget *plgList) : 
	pluginConfigFrame(plgCnfFrm),
	pluginListWidget(plgList),
	flushNow(0),
	proxy(NULL)
{
	memset((char *)gfxBuffer, 0x00, 2048);
	memset((char *)CRC, 0x00, 64);
}


//Adding the plugins to the lists maybe needs to be handled outside this class.
//Haven't figured this one out yet
void cPluginHandler::addPlugin(cPlugin *plugin)
{
	//maintain a list of plugins in memory
	pluginList[plugin->getName()] = plugin;

	QListWidgetItem *newListItem = new QListWidgetItem;
	newListItem->setText(QString::fromStdString(plugin->getName()));
	pluginListWidget->addItem(newListItem);

	//add a pointer to the graphics buffer to the plugin
	plugin->gfxBuff = (char *)gfxBuffer;
	plugin->master = this;

	//set some fake limits for the plugin
	plugin->maxX = 256;
	plugin->maxY = 64;
	//NOTE: This is just a fake run, this will need to be handles when the thread starts
	plugin->run();
}

void cPluginHandler::setPluginActive(cPlugin *plugin)
{
	//maintain a list of active plugins
	activePlugins[plugin->getName()] = plugin;
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


/*
 * TODO: These 2 methods below need to be mutex locked
 */
void cPluginHandler::incFlushFlag()
{
	flushNow += 1;
}
void cPluginHandler::deIncFlushFlag()
{
	flushNow -= 1;
}

/*
 * TODO: This has concurancy issues
 */
void cPluginHandler::run()
{
	while(1)
	{
		if(flushNow)
		{
			flush();
			deIncFlushFlag();
		}
	}
}



/*
 * for(uint32_t Address = 0; Address < FLASHEND; Address++)
 * {
 * 	FlashCRC = CRC16(FlashCRC, pgm_read_byte_far(Address));
 * }
 */



cPluginHandler::~cPluginHandler()
{
}

