/* 
 * File:   cVector.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 4:44 PM
 */

#include "cVector.h"

cVector::cVector() : x(0), y(0)
{
}

cVector::cVector(int xIn, int yIn) : x(xIn), y(yIn)
{
}

int cVector::getX()
{
	return x;
}
int cVector::getY()
{
	return y;
}
void cVector::setX(int xIn)
{
	x = xIn;
}
void cVector::setY(int yIn)
{
	y = yIn;
}

cVector::~cVector()
{
}

