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
private:
	std::vector<int> values;
	int max;
	int min;
	int numValues;
	int avgValue;

};

#endif	/* _CLINE_H */

