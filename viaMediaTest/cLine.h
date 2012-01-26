/* 
 * File:   cLine.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 4:43 PM
 */

#ifndef _CLINE_H
#define	_CLINE_H

#include "cVector.h"
#include <list>

class cLine
{
public:
	cLine();
	cLine(cVector point0, cVector point1, cVector point2, cVector point3);
	virtual ~ cLine();
private:
	std::list<cVector> points;
};

#endif	/* _CLINE_H */

