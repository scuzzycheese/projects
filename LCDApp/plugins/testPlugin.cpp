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
		for(int i = 0; i < maxX; i ++)
		{
			setPixel(i, 0);
		}
		for(int i = 0; i < maxX; i ++)
		{
			setPixel(i, maxY - 1);
		}

		for(int i = 0; i < maxY; i ++)
		{
			setPixel(0, i);
		}
		for(int i = 0; i < maxY; i ++)
		{
			setPixel(maxX - 1, i);
		}

		//flush changes from the buffer to the device
		flushNow();
		sleep(10);
	}

}

void testPlugin::reDraw()
{
		for(int i = 0; i < maxX; i ++)
		{
			setPixel(i, 0);
		}
		for(int i = 0; i < maxX; i ++)
		{
			setPixel(i, maxY - 1);
		}

		for(int i = 0; i < maxY; i ++)
		{
			setPixel(0, i);
		}
		for(int i = 0; i < maxY; i ++)
		{
			setPixel(maxX - 1, i);
		}
		flushNow();
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

