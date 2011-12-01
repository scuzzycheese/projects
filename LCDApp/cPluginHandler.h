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

class cPluginHandler
{
public:
	cPluginHandler(QFrame *plgCnfFrm, QListWidget *plgList);
	cPluginHandler(const cPluginHandler& orig);

	void mAddPlugin(cPlugin *plugin);

	virtual ~ cPluginHandler();
private:

	QFrame *pluginConfigFrame;
	QListWidget *pluginListWidget;

	QList<cPlugin *> pluginList;

};

#endif	/* _CPLUGINHANDLER_H */

