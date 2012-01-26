/* 
 * File:   cLine.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 4:43 PM
 */

#ifndef _CLINE_H
#define	_CLINE_H

#include "cVector.h"

class cLine
{
public:
	cLine();
	cLine(cVector start, cVector end);
	cLine(int x1, int y1, int x2, int y2);
	virtual ~ cLine();
private:
	cVector start;
	cVector end;
};

#endif	/* _CLINE_H */

