/* 
 * File:   cQPluginHelper.h
 * Author: scuzzy
 *
 * Created on 14 January 2012, 9:53 PM
 */

#ifndef _CQPLUGINHELPER_H
#define	_CQPLUGINHELPER_H

#include "cDockMainWindow.h"
#include "cPluginHandler.h"
#include <QObject>

class cQPluginHelper : public QObject
{
	Q_OBJECT

public:
	cQPluginHelper(QListWidget *plgList);
	void addPlugin(std::string name);
	void addPluginHandlerAndDock(cPluginHandler *plgHandler, cDockMainWindow *dock, std::string deviceName);
	virtual ~cQPluginHelper();
private:
	std::map<std::string, cPluginHandler *>pluginHandlers;
	std::map<std::string, cDockMainWindow *>dockWindows;
	QListWidget *pluginListWidget;

public slots:
	void addPluginToDock();


};

#endif	/* _CQPLUGINHELPER_H */

