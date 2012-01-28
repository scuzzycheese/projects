/* 
 * File:   cRectangle.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 8:07 PM
 */

#include "cRectangle.h"

cRectangle::cRectangle()
{
}

cRectangle::cRectangle(int x1, int y1, int x2, int y2)
{
	build(x1, y1, x2, y2);
}

void cRectangle::build(int x1, int y1, int x2, int y2)
{
	if(x1 < x2 && y1 < y2)
	{
		addVector(BOTTOM_LEFT, cVector(x1, y1));
		addVector(TOP_RIGHT, cVector(x2, y2));
	}
}

void cRectangle::buildFromLineRep(cLineRep line)
{
	std::vector<int> values = line.getValues();
	if(values.size() == 4)
	{
		setName(line.getName());
		if((values[0] < values[2]) && (values[1] < values[3]))
		{
			addVector(cVector(values[0], values[1]));
			addVector(cVector(values[2], values[3]));
		}
		else
		{
			std::cout << "Error, rectangle definition incorrect" << std::endl;
		}
	}
	else
	{
		std::cout << "Error building cRectangle from cLineRep, wrong number of values" << std::endl;
	}
}


cVector cRectangle::getBottomLeft()
{
	return getVector(BOTTOM_LEFT);
}
cVector cRectangle::getTopRight()
{
	return getVector(TOP_RIGHT);
}

bool cRectangle::collide(cRectangle &rec)
{
	bool xOverlap = (getVector(BOTTOM_LEFT).getX() < rec.getVector(TOP_RIGHT).getX()) && (getVector(TOP_RIGHT).getX() > rec.getVector(BOTTOM_LEFT).getX());
	bool yOverlap = (getVector(BOTTOM_LEFT).getY() < rec.getVector(TOP_RIGHT).getY()) && (getVector(TOP_RIGHT).getY() > rec.getVector(BOTTOM_LEFT).getY());
	if(xOverlap && yOverlap)
	{
		mCollidesWith[rec.getName()] = &rec;
		rec.mCollidesWith[getName()] = this;
		return true;
	}
	else return false;
}

bool cRectangle::contains(cRectangle &rec)
{
	bool xContains = (rec.getVector(BOTTOM_LEFT).getX() >= getVector(BOTTOM_LEFT).getX()) && (rec.getVector(TOP_RIGHT).getX() <= getVector(TOP_RIGHT).getX());
	bool yContains = (rec.getVector(BOTTOM_LEFT).getY() >= getVector(BOTTOM_LEFT).getY()) && (rec.getVector(TOP_RIGHT).getY() <= getVector(TOP_RIGHT).getY());
	if(xContains && yContains)
	{
		mContains[rec.getName()] = &rec;
		rec.mContainedBy[getName()] = this;
		return true;
	}
	else return false;
}

bool cRectangle::touches(cRectangle &rec)
{
	bool xOverlap = (getVector(BOTTOM_LEFT).getX() <= rec.getVector(TOP_RIGHT).getX()) && (getVector(TOP_RIGHT).getX() >= rec.getVector(BOTTOM_LEFT).getX());
	bool yTouches = (getVector(BOTTOM_LEFT).getY() == rec.getVector(TOP_RIGHT).getY()) || (getVector(TOP_RIGHT).getY() == rec.getVector(BOTTOM_LEFT).getY());

	bool yOverlap = (getVector(BOTTOM_LEFT).getY() <= rec.getVector(TOP_RIGHT).getY()) && (getVector(TOP_RIGHT).getY() >= rec.getVector(BOTTOM_LEFT).getY());
	bool xTouches = (getVector(BOTTOM_LEFT).getX() == rec.getVector(TOP_RIGHT).getX()) || (getVector(TOP_RIGHT).getX() == rec.getVector(BOTTOM_LEFT).getX());

	if((xOverlap && yTouches) || (yOverlap && xTouches))
	{
		mTouches[rec.getName()] = &rec;
		rec.mTouches[getName()] = this;
		return true;
	}
	else return false;
}



cRectangle::~cRectangle()
{
}

