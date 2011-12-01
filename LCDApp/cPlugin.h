/* 
 * File:   cPlugin.h
 * Author: scuzzy
 *
 * Created on 01 December 2011, 4:34 PM
 */

#ifndef _CPLUGIN_H
#define	_CPLUGIN_H
#include <QString>

class cPlugin
{
public:
	cPlugin();
	cPlugin(const cPlugin& orig);

	QString getName();

	virtual ~ cPlugin();
private:

};

#endif	/* _CPLUGIN_H */

