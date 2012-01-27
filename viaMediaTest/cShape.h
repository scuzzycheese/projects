/* 
 * File:   cShape.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 4:42 PM
 */

#ifndef _CSHAPE_H
#define	_CSHAPE_H

#include "cLine.h"
#include <map>
#include <iostream>

class cShape
{
public:
	cShape();
	virtual ~cShape();
	void addLine(cLine line);
	void addLine(int lineNumber, cLine line);
	cLine getLine(int lineNumber);
	void setName(std::string name);
	std::string getName();
protected:
	std::map<int, cLine> lines;
	std::string name;

};

#endif	/* _CSHAPE_H */

