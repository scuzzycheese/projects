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

	bool collide(cRectangle &rec);
	bool contains(cRectangle &rec);
	bool touches(cRectangle &rec);

	virtual ~ cRectangle();
	enum
	{
		BOTTOM_LEFT = 0,
		TOP_RIGHT
	};
private:
	void build(int x1, int y1, int x2, int y2);

};

#endif	/* _CRECTANGLE_H */

