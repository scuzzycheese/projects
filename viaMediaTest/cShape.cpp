/* 
 * File:   cRectangle.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 4:41 PM
 */

#include "cShape.h"

cShape::cShape()
{
}
void cShape::addLine(cLine line)
{
	lines.push_back(line);
}

void cShape::addLine(int lineNumber, cLine line)
{
	lines[lineNumber] = line;
}

cLine cShape::getLine(int lineNumber)
{
	/**
	 * TODO: check this isn't going to cause problems
	 * when fetching a non existant line
	 */
	return lines[lineNumber];
}

void cShape::setName(std::string name)
{
	this->name = name;
}
std::string cShape::getName()
{
	return name;
}

cShape::~cShape()
{
}

