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
	if(vectors.size() > 0)
	vectors[(vectors.size() > 0) ? vectors.end()->first : 0] = vector;
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

cShape::cShape(cLineRep line)
{
	buildFromLineRep(line);
}
void cShape::buildFromLineRep(cLineRep line)
{
	std::vector<int> values = line.getValues();
	if(!(values.size() % 2))
	{
		setName(line.getName());
		for(std::vector<int>::iterator valIt = values.begin(); valIt < values.end(); valIt += 2)
		{
			addVector(cVector(*valIt, *(valIt + 1)));
		}
	}
}

cShape::~cShape()
{
}

