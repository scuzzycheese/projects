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
void cShape::addVector(cVector vector)
{
	vectors[(vectors.size() > 0) ? vectors.end()->first + 1 : 0] = vector;
}

void cShape::addVector(int vecNumber, cVector vector)
{
	vectors[vecNumber] = vector;
}

cVector cShape::getVector(int vecNumber)
{
	return vectors[vecNumber];
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

