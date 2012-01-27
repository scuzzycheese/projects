/* 
 * File:   cParse.h
 * Author: scuzzy
 *
 * Created on 27 January 2012, 11:24 PM
 */

#ifndef _CPARSE_H
#define	_CPARSE_H

#include "cLineRep.h"

class cParse
{
public:
	cParse();
	virtual std::vector<cLineRep> fetchLines() = 0;
	virtual ~ cParse();
protected:
	std::vector<cLineRep> lines;

};

#endif	/* _CPARSE_H */

