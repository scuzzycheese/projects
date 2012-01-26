/* 
 * File:   cLine.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 4:43 PM
 */

#include "cLine.h"

cLine::cLine() : start(0, 0), end(0, 0)
{
}

cLine::cLine(cVector start, cVector end) : start(start), end(end)
{
}

cLine::cLine(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2)
{
}

cLine::~cLine()
{
}

