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

void cPluginHandler::mAddPlugin(cPlugin *plugin)
{
	pluginList.append(plugin);

	QListWidgetItem *newListItem = new QListWidgetItem;
	newListItem->setText(plugin->getName());
	pluginListWidget->addItem(newListItem);
}

cPluginHandler::~cPluginHandler()
{
}

