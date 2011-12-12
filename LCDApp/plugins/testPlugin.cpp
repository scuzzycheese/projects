/* 
 * File:   testPlugin.cpp
 * Author: scuzzy
 * 
 * Created on 05 December 2011, 2:02 PM
 */

#include "testPlugin.h"

testPlugin::testPlugin()
{
	setName("Test Plugin");
}

void testPlugin::run()
{
	std::cout << "running test plugin" << std::endl;

	for(int i = 0; i < 256; i += 2)
	{
		setPixel(i, 0);
	}

	for(int i = 0; i < 64; i += 2)
	{
		setPixel(255, i);
	}

	setPixel(10, 0);
	setPixel(10, 2);
	setPixel(10, 4);
	setPixel(10, 6);
	setPixel(10, 8);
	setPixel(10, 10);



	setPixel(0, 10);
	setPixel(2, 10);
	setPixel(4, 10);
	setPixel(6, 10);
	setPixel(8, 10);
	setPixel(0, 10);


	setPixel(255, 0);
	setPixel(255, 63);
	setPixel(0, 63);
	setPixel(0, 0);


	flushNow();

	while(true)
	{
		sleep(10);
	}

}


testPlugin::~testPlugin()
{
}


cPlugin *getPluginInstance()
{
	return new testPlugin();
}

