/* 
 * File:   cPluginHandler.h
 * Author: scuzzy
 *
 * Created on 01 December 2011, 3:29 PM
 */

#ifndef _CPLUGINHANDLER_H
#define	_CPLUGINHANDLER_H

#include <QFrame>
#include <QListWidget>
#include <QListWidgetItem>
#include "cPlugin.h"
#include <iostream>
#include <inttypes.h>

#include "cLM6800Proxy.h"

class cPluginHandler
{
public:
	cPluginHandler(QFrame *plgCnfFrm, QListWidget *plgList);

	void addPlugin(cPlugin *plugin);
	void setPluginActive(cPlugin *plugin);
	//TODO: maybe make the proxy a base class so it's proxy type ignorant
	void setProxy(cLM6800Proxy *proxy);
	uint16_t crc16(uint16_t crc, uint8_t a);
	void flush();
	void incFlushFlag();
	void deIncFlushFlag();

	void run();

	virtual ~ cPluginHandler();
private:

	QFrame *pluginConfigFrame;
	QListWidget *pluginListWidget;

	std::map<std::string, cPlugin *> pluginList;
	std::map<std::string, cPlugin *> activePlugins;



	char gfxBuffer[4][8][64];
	uint16_t CRC[4][8];

	cLM6800Proxy *proxy;

	int flushNow;

};

#endif	/* _CPLUGINHANDLER_H */

