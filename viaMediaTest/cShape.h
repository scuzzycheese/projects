/* 
 * File:   cShape.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 4:42 PM
 */

#ifndef _CSHAPE_H
#define	_CSHAPE_H

#include "cVector.h"
#include <map>
#include <iostream>

class cShape
{
public:
	cShape();
	virtual ~cShape();
	void addVector(cVector vector);
	void addVector(int vecNumber, cVector vector);
	cVector getVector(int vecNumber);
	void setName(std::string name);
	std::string getName();
protected:
	std::map<int, cVector> vectors;
	std::string name;

};

#endif	/* _CSHAPE_H */

