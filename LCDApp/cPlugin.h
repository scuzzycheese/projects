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

class cPlugin
{
public:
	cPlugin();
	cPlugin(const cPlugin& orig);

	void setName(const std::string &name);
	std::string getName();

	virtual ~ cPlugin();
private:
	std::string pluginName;

};

#endif	/* _CPLUGIN_H */

