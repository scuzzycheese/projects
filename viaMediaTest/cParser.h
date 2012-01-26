/* 
 * File:   cParser.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 11:30 PM
 */

#ifndef _CPARSER_H
#define	_CPARSER_H

#include <iostream>
#include <vector>
#include "cShape.h"
#include "cRectangle.h"

class cParser
{
public:
	cParser();
	cParser(std::string file);
	virtual ~ cParser();
private:
	std::vector<cShape> shapes;

};

#endif	/* _CPARSER_H */

