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
#include "cLineRep.h"
#include "cParse.h"

class cParseFromFile : public cParse
{
public:
	cParseFromFile();
	cParseFromFile(std::string file);
	std::vector<cLineRep> fetchLines();
	virtual ~cParseFromFile();
private:
	void parse(std::string file);

};

#endif	/* _CPARSER_H */

