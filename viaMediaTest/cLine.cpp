/* 
 * File:   cLine.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 4:43 PM
 */

#include "cLine.h"

cLine::cLine()
{
}

cLine::cLine(cVector point0, cVector point1, cVector point2, cVector point3)
{
	points.push_back(point0);
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);
}

cLine::~cLine()
{
}

