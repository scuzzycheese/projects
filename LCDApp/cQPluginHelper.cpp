/* 
 * File:   cQPluginHelper.cpp
 * Author: scuzzy
 * 
 * Created on 14 January 2012, 9:53 PM
 */

#include "cQPluginHelper.h"

cQPluginHelper::cQPluginHelper(QListWidget *plgList) : pluginListWidget(plgList)
{
}

void cQPluginHelper::addPluginToDock()
{
	QList<QListWidgetItem *> selectedPlugins = pluginListWidget->selectedItems();
	for(int i = 0; i < selectedPlugins.size(); ++ i)
	{
		QListWidgetItem *selectedPlugin = selectedPlugins.at(i);

		cPlugin *plugin = pluginHandlers[selectedPlugin->text().toStdString()]->addPluginInstance(selectedPlugin->text().toStdString());

		if(plugin)
		{
			dockWindows[selectedPlugin->text().toStdString()]->addPluginToDock(plugin);
		}
	}
}

void cQPluginHelper::addPluginHandlerAndDock(cPluginHandler *plgHandler, cDockMainWindow *dock, std::string deviceName)
{
	pluginHandlers[deviceName] = plgHandler;
	dockWindows[deviceName] = dock;
}

void cQPluginHelper::addPlugin(std::string pluginName)
{
	QListWidgetItem *newListItem = new QListWidgetItem;
	newListItem->setText(QString::fromStdString(pluginName));
	pluginListWidget->addItem(newListItem);
}

cQPluginHelper::~cQPluginHelper()
{
}

