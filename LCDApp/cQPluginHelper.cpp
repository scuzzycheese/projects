/* 
 * File:   cQPluginHelper.cpp
 * Author: scuzzy
 * 
 * Created on 14 January 2012, 9:53 PM
 */

#include "cQPluginHelper.h"

cQPluginHelper::cQPluginHelper(QListWidget *plgList, QComboBox *devComboBox) :
	pluginListWidget(plgList),
	deviceComboBox(devComboBox)
{
}

void cQPluginHelper::activatePlugin()
{
	QList<QListWidgetItem *> selectedPlugins = pluginListWidget->selectedItems();
	for(int i = 0; i < selectedPlugins.size(); ++ i)
	{
		QListWidgetItem *selectedPlugin = selectedPlugins.at(i);

		cPlugin *plugin = pluginHandlers[deviceComboBox->currentText().toStdString()]->addPluginInstance(selectedPlugin->text().toStdString());

		if(plugin)
		{
			dockWindows[deviceComboBox->currentText().toStdString()]->addPluginToDock(plugin);
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

