#ifndef _CLINE_H
#define	_CLINE_H

#include <iostream>
#include <vector>

class cLine
{
public:
	cLine(std::string);
	bool validLine();
	std::string getOriginalLine();
	virtual ~ cLine();

   unsigned int getAvgValue() const;
   unsigned int getNumValues() const;
   unsigned int getMin() const;
   unsigned int getMax() const;

   std::vector<unsigned int> getValues() const;

private:
	unsigned int max;
	unsigned int min;
	unsigned int numValues;
	unsigned int avgValue;
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

