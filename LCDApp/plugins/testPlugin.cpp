/* 
 * File:   testPlugin.cpp
 * Author: scuzzy
 * 
 * Created on 05 December 2011, 2:02 PM
 */

#include "testPlugin.h"

testPlugin::testPlugin()
{
	setName(getPluginName());
}

void testPlugin::run()
{
	std::cout << "running test plugin" << std::endl;

	while(true)
	{
		for(int i = 0; i < maxX; i += 2)
		{
			setPixel(i, 0);
		}

		for(int i = 0; i < maxY; i += 2)
		{
			setPixel(maxX - 1, i);
		}
		//flush changes from the buffer to the device
		flushNow();
		sleep(1);
	}

}


testPlugin::~testPlugin()
{
}

QString getPluginName()
{
	return QString("Test Plugin");
}

cPlugin *getPluginInstance()
{
	return new testPlugin;
}

