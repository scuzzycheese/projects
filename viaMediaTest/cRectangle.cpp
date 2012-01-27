/* 
 * File:   cRectangle.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 8:07 PM
 */

#include "cRectangle.h"

cRectangle::cRectangle(int x1, int y1, int x2, int y2)
{
	build(x1, y1, x2, y2);
}

void cRectangle::build(int x1, int y1, int x2, int y2)
{
	addVector(BOTTOM_LEFT, cVector(x1, y1));
	addVector(TOP_RIGHT, cVector(x2, y2));
}


cRectangle::~cRectangle()
{
}

