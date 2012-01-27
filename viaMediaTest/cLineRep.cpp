/* 
 * File:   cLineRep.cpp
 * Author: scuzzy
 * 
 * Created on 27 January 2012, 10:45 PM
 */

#include "cLineRep.h"

cLineRep::cLineRep()
{
}

cLineRep::cLineRep(std::string name) : name(name)
{
}

cLineRep::cLineRep(std::string name, std::vector<int> vals) : name(name), values(vals)
{
}

void cLineRep::addValue(int val)
{
	values.push_back(val);
}

void cLineRep::addValues(std::vector<int> vals)
{
	values.insert(values.end(), vals.begin(), vals.end());
}

void cLineRep::setName(std::string name)
{
	this->name = name;
}

std::string cLineRep::getName()
{
	return name;
}

std::vector<int> cLineRep::getValues()
{
	return values;
}

int cLineRep::at(int index)
{
	return values[index];
}

int cLineRep::numVals()
{
	return values.size();
}


cLineRep::~cLineRep()
{
}

