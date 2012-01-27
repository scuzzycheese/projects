/* 
 * File:   cLineRep.h
 * Author: scuzzy
 *
 * Created on 27 January 2012, 10:45 PM
 */

#ifndef _CLINEREP_H
#define	_CLINEREP_H

#include <iostream>
#include <vector>

class cLineRep
{
public:
	cLineRep();
	cLineRep(std::string name);
	cLineRep(std::string name, std::vector<int> vals);
	void addValue(int val);
	void addValues(std::vector<int> vals);
	void setName(std::string name);
	std::string getName();
	std::vector<int> getValues();
	int at(int index);
	int numVals();
	virtual ~ cLineRep();
private:
	std::string name;
	std::vector<int> values;

};

#endif	/* _CLINEREP_H */

