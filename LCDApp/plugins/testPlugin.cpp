/* 
 * File:   testPlugin.cpp
 * Author: scuzzy
 * 
 * Created on 05 December 2011, 2:02 PM
 */

#include "testPlugin.h"
#include "cPlugin.h"

testPlugin::testPlugin()
{
}

void testPlugin::run()
{
	setPixel(10, 10);
	flushNow();
}


testPlugin::~testPlugin()
{
}


cPlugin *getPluginInstance()
{
	return new testPlugin();
}

