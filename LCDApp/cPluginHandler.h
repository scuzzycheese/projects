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

class cPluginHandler
{
public:
	cPluginHandler(QFrame *plgCnfFrm, QListWidget *plgList);
	cPluginHandler(const cPluginHandler& orig);

	void addPlugin(cPlugin *plugin);
	void setPluginActive(cPlugin *plugin);

	virtual ~ cPluginHandler();
private:

	QFrame *pluginConfigFrame;
	QListWidget *pluginListWidget;

	std::map<std::string, cPlugin *> pluginList;
	std::map<std::string, cPlugin *> activePlugins;

};

#endif	/* _CPLUGINHANDLER_H */

