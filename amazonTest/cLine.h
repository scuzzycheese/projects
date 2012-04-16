#ifndef _CLINE_H
#define	_CLINE_H

#include <iostream>
#include <vector>

class cLine
{
public:
	cLine();
	cLine(std::string);
	virtual ~ cLine();
	unsigned int max;
	unsigned int min;
	unsigned int numValues;
	unsigned int avgValue;
private:
	std::vector<unsigned int> values;

};

#endif	/* _CLINE_H */

