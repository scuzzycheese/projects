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


class cUdev
{
public:
	cUdev();
	virtual ~ cUdev();



private:

	std::list<std::string> findDevices(std::string mnfturer);

	std::list<std::string> devices;

};

#endif	/* _CUDEV_H */

