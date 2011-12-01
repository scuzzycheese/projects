/* 
 * File:   cPlugin.cpp
 * Author: scuzzy
 * 
 * Created on 01 December 2011, 4:34 PM
 */

#include "cPlugin.h"

cPlugin::cPlugin()
{
}

QString cPlugin::getName()
{
	return pluginName;
}

void cPlugin::setName(const QString &name)
{
	pluginName = name;
}

cPlugin::cPlugin(const cPlugin& orig)
{
}

cPlugin::~cPlugin()
{
}

