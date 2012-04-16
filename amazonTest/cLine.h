#ifndef _CLINE_H
#define	_CLINE_H

#include <iostream>
#include <vector>

class cLine
{
public:
	cLine();
	cLine(std::string);
	bool validLine();
	std::string origin();
	virtual ~ cLine();
	unsigned int max;
	unsigned int min;
	unsigned int numValues;
	unsigned int avgValue;
private:
	std::string originalLine;
	std::vector<unsigned int> values;
	struct retVal
	{
		bool validValue;
		unsigned int value;
	};
	retVal convertToInt(std::string value);

};

#endif	/* _CLINE_H */

