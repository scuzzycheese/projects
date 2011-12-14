/* 
 * File:   testPlugin.h
 * Author: scuzzy
 *
 * Created on 05 December 2011, 2:02 PM
 */

#ifndef _TESTPLUGIN_H
#define	_TESTPLUGIN_H

#include "cPlugin.h"

class testPlugin : public cPlugin
{
public:
	testPlugin();

	virtual ~ testPlugin();

	void run();

	void reDraw();


private:

};


QString getPluginName();
cPlugin *getPluginInstance();

#endif	/* _TESTPLUGIN_H */

