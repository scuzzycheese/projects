/* 
 * File:   cRectangle.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 8:07 PM
 */

#ifndef _CRECTANGLE_H
#define	_CRECTANGLE_H

#include "cShape.h"
#include <iostream>

class cRectangle : public cShape
{
public:
	cRectangle(int x1, int y1, int x2, int y2);
	cLine getLeftLine();
	cLine getTopLine();
	cLine getRightLine();
	cLine getBottomLine();

	void setLeftLine(cLine leftLine);
	void setTopLine(cLine topLine);
	void setRightLine(cLine rightLine);
	void setBottomLine(cLine bottomLine);

	void build(int x1, int y1, int x2, int y2);
	virtual ~ cRectangle();
	enum
	{
		LEFT_LINE = 0,
		TOP_LINE,
		RIGHT_LINE,
		BOTTOM_LINE
	};
private:

};

#endif	/* _CRECTANGLE_H */

