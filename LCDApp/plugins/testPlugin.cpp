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

	int x = 0;
	int incX = 1;
	int y = 0;
	int incY = 1;
	while(true)
	{
		clrScreen();
		for(int i = 0; i < width; i ++)
		{
			setPixel(i, 0);
		}
		for(int i = 0; i < width; i ++)
		{
			setPixel(i, height - 1);
		}

		for(int i = 0; i < height; i ++)
		{
			setPixel(0, i);
		}
		for(int i = 0; i < height; i ++)
		{
			setPixel(width - 1, i);
		}


		setPixel(x, y);
		setPixel(x + 1, y);
		setPixel(x + 1, y + 1);
		setPixel(x, y + 1);
		setPixel(x - 1, y);
		setPixel(x - 1, y - 1);
		setPixel(x, y - 1);
		setPixel(x - 1, y + 1);
		setPixel(x + 1, y - 1);

		if(x >= width) incX = -1;
		if(y >= height) incY = -1;
		if(x <= 0) incX = 1;
		if(y <= 0) incY = 1;

		x += incX;
		y += incY;

		//flush changes from the buffer to the device
		flushNow();
		msleep(25);
	}

}

void testPlugin::reDraw()
{
		for(int i = 0; i < width; i ++)
		{
			setPixel(i, 0);
		}
		for(int i = 0; i < width; i ++)
		{
			setPixel(i, height - 1);
		}

		for(int i = 0; i < height; i ++)
		{
			setPixel(0, i);
		}
		for(int i = 0; i < height; i ++)
		{
			setPixel(width - 1, i);
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

