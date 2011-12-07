/* 
 * File:   cPlugin.h
 * Author: scuzzy
 *
 * Created on 01 December 2011, 4:34 PM
 */

#ifndef _CPLUGIN_H
#define	_CPLUGIN_H
#include <QString>
#include <iostream>

//nasty forward declaration
class cPluginHandler;

class cPlugin
{
public:
	cPlugin();
	cPlugin(const cPlugin& orig);

	void setName(const std::string &name);
	std::string getName();

	void setPixel(int x, int y);
	void clearPixel(int x, int y);

	virtual void run() = 0;

	void flushNow();

	virtual ~cPlugin();

private:
	friend class cPluginHandler;

	std::string pluginName;

	int maxX;
	int maxY;
	int startX;
	int startY;

	char *gfxBuff;

	cPluginHandler *master;

};

#endif	/* _CPLUGIN_H */

