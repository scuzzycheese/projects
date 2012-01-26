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
	addLine(LEFT_LINE, cLine(x1, y1, x1, y2));
	addLine(TOP_LINE, cLine(x1, y2, x2, y2));
	addLine(RIGHT_LINE, cLine(x2, y2, x2, y1));
	addLine(BOTTOM_LINE, cLine(x2, y1, x1, y1));
}

cLine cRectangle::getLeftLine()
{
	return lines[LEFT_LINE];
}
cLine cRectangle::getTopLine()
{
	return lines[TOP_LINE];
}
cLine cRectangle::getRightLine()
{
	return lines[RIGHT_LINE];
}
cLine cRectangle::getBottomLine()
{
	return lines[BOTTOM_LINE];
}

void cRectangle::setLeftLine(cLine leftLine)
{
	lines[LEFT_LINE] = leftLine;
}
void cRectangle::setTopLine(cLine topLine)
{
	lines[TOP_LINE] = topLine;
}
void cRectangle::setRightLine(cLine rightLine)
{
	lines[RIGHT_LINE] = rightLine;
}
void cRectangle::setBottomLine(cLine bottomLine)
{
	lines[BOTTOM_LINE] = bottomLine;
}

cRectangle::~cRectangle()
{
}

