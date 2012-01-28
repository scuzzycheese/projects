/* 
 * File:   cShape.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 4:42 PM
 */

#ifndef _CSHAPE_H
#define	_CSHAPE_H

#include "cVector.h"
#include "cLineRep.h"
#include <map>
#include <iostream>

class cShape
{
public:
	cShape();
	cShape(cLineRep line);
	virtual void buildFromLineRep(cLineRep line);
	virtual ~cShape();
	void addVector(cVector vector);
	void addVector(int vecNumber, cVector vector);
	cVector getVector(int vecNumber);
	void setName(std::string name);
	std::string getName();

	/**
	 * TODO: provide accessors
	 */
	std::map<std::string, cShape *>mCollidesWith;
	std::map<std::string, cShape *>mContains;
	std::map<std::string, cShape *>mContainedBy;
	std::map<std::string, cShape *>mTouches;
protected:
	std::map<int, cVector> vectors;
	std::string name;

};

#endif	/* _CSHAPE_H */

