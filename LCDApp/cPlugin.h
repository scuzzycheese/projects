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
#include <QThread>
#include "cQueue.h"

//nasty forward declaration
class cPluginHandler;

class cPlugin : public QThread
{

	Q_OBJECT

public:
	cPlugin();

	std::string getName();

	void setPixel(int x, int y);
	void clearPixel(int x, int y);

	void setQueue(cQueue *q);

	void flushNow();

	virtual ~cPlugin();

protected:

	virtual void run() = 0;

	void setName(const std::string &name);

	cQueue *queue;

private:
	friend class cPluginHandler;

	std::string pluginName;

	int maxX;
	int maxY;
	int startX;
	int startY;

	char *gfxBuff;


};

#endif	/* _CPLUGIN_H */

