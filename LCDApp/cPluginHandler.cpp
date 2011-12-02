/* 
 * File:   cPluginHandler.cpp
 * Author: scuzzy
 * 
 * Created on 01 December 2011, 3:29 PM
 */

#include "cPluginHandler.h"

cPluginHandler::cPluginHandler(QFrame *plgCnfFrm, QListWidget *plgList) : pluginConfigFrame(plgCnfFrm), pluginListWidget(plgList)
{



}

cPluginHandler::cPluginHandler(const cPluginHandler& orig)
{
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
}

void cPluginHandler::setPluginActive(cPlugin *plugin)
{
	//maintain a list of active plugins
	activePlugins[plugin->getName()] = plugin;
}

cPluginHandler::~cPluginHandler()
{
}

