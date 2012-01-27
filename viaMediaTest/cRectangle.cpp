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

bool cRectangle::collide(cRectangle &rec)
{
	bool xOverlap = (getVector(BOTTOM_LEFT).getX() <= rec.getVector(TOP_RIGHT).getX()) && (getVector(TOP_RIGHT).getX() >= rec.getVector(BOTTOM_LEFT).getX());
	bool yOverlap = (getVector(BOTTOM_LEFT).getY() <= rec.getVector(TOP_RIGHT).getY()) && (getVector(TOP_RIGHT).getY() >= rec.getVector(BOTTOM_LEFT).getY());
	return xOverlap && yOverlap;
}

bool cRectangle::contains(cRectangle &rec)
{
	bool xContains = (rec.getVector(BOTTOM_LEFT).getX() >= getVector(BOTTOM_LEFT).getX()) && (rec.getVector(TOP_RIGHT).getX() <= getVector(TOP_RIGHT).getX());
	bool yContains = (rec.getVector(BOTTOM_LEFT).getY() >= getVector(BOTTOM_LEFT).getY()) && (rec.getVector(TOP_RIGHT).getY() <= getVector(TOP_RIGHT).getY());
	return xContains && yContains;
}

bool cRectangle::touches(cRectangle &rec)
{
	bool xOverlap = (getVector(BOTTOM_LEFT).getX() <= rec.getVector(TOP_RIGHT).getX()) && (getVector(TOP_RIGHT).getX() >= rec.getVector(BOTTOM_LEFT).getX());
	bool yTouches = (getVector(BOTTOM_LEFT).getY() == rec.getVector(TOP_RIGHT).getY()) || (getVector(TOP_RIGHT).getY() == rec.getVector(BOTTOM_LEFT).getY());

	bool yOverlap = (getVector(BOTTOM_LEFT).getY() <= rec.getVector(TOP_RIGHT).getY()) && (getVector(TOP_RIGHT).getY() >= rec.getVector(BOTTOM_LEFT).getY());
	bool xTouches = (getVector(BOTTOM_LEFT).getX() == rec.getVector(TOP_RIGHT).getX()) || (getVector(TOP_RIGHT).getX() == rec.getVector(BOTTOM_LEFT).getX());

	return (xOverlap && yTouches) || (yOverlap && xTouches);
}



cRectangle::~cRectangle()
{
}

