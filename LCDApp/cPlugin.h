/* 
 * File:   cPlugin.h
 * Author: scuzzy
 *
 * Created on 01 December 2011, 4:34 PM
 */

#ifndef _CPLUGIN_H
#define	_CPLUGIN_H
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
	void setName(std::string name);

	void setPixel(int x, int y);
	void clearPixel(int x, int y);


	void flushNow();

	void clrScreen();

	virtual ~cPlugin();

	void setMaxX(int x);
	void setMaxY(int y);
	void setStartX(int x);
	void setStartY(int y);
	void setWidth(int x);
	void setHeight(int y);

	virtual void reDraw() = 0;

protected:

	virtual void run() = 0;

	cQueue *queue;

	int width;
	int height;

private:
	friend class cPluginHandler;

	void setQueue(cQueue *q);

	int maxX;
	int maxY;
	int startX;
	int startY;

	std::string pluginName;

	char *gfxBuff;




};



#endif	/* _CPLUGIN_H */

