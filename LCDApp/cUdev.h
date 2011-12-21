/* 
 * File:   cUdev.h
 * Author: scuzzy
 *
 * Created on 18 December 2011, 10:58 PM
 */

#ifndef _CUDEV_H
#define	_CUDEV_H

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <list>
#include <iostream>
#include <map>


class cUdev
{
public:
	cUdev();
	virtual ~ cUdev();

	std::list<std::string> getLCDDevices();
	std::list<std::string> getBootloaderDevices();


private:

	std::map<std::string, udev_device *> findDevices();

	std::list<std::string> devices;

};

#endif	/* _CUDEV_H */

