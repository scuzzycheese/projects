#include "cLine.h"
#include <sstream>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>


cLine::cLine(std::string line) : min(LONG_MAX), max(0), numValues(0), avgValue(0)
{
	std::istringstream ssLine(line);
	long long totalValue = 0;
	originalLine = line;
	while(ssLine.good())
	{
		std::string token;
		std::getline(ssLine, token, ' ');


		retVal ret = convertToInt(token);

		if(ret.validValue)
		{
			if(ret.value < min) min = ret.value;
			if(ret.value > max) max = ret.value;
			numValues ++;
			totalValue += ret.value;
			values.push_back(ret.value);
		}

	}
	if(totalValue > 0 && numValues > 0)
	{
		//std::cout << "TOTAL: " << totalValue << std::endl;
		//std::cout << "NUMVALUES: " << numValues << std::endl;
		avgValue = totalValue / numValues;
	}
}

cLine::retVal cLine::convertToInt(std::string value)
{
	retVal ret = {false, 0};
	char *endptr;
	//std::cout << "Interpreted Values: ";
	if(!value.empty())
	{
		errno = 0;
		long long intVal = strtol(value.c_str(), &endptr, 10);
		if(errno == ERANGE && (intVal == LONG_MAX || intVal == LONG_MIN))
		{
			std::cout << "Bad Value(leaving out of set): " << value << std::flush;
			perror(" ");
		}
		else if(intVal < 0)
		{
			std::cout << "Bad Value(leaving out of set): " << value << " : Negative number" << std::endl;
		}
		else if(value.c_str() == endptr)
		{
			std::cout << "Bad Value(leaving out of set): " << value << " : Invalid number" << std::endl;
		}
		else
		{
			if(intVal >= 0 && errno == 0)
			{
				ret.validValue = true;
				ret.value = intVal;
				//std::cout << intVal << " ";
			}
		}
	}
	//std::cout << std::endl;
	return ret;
}

bool cLine::validLine()
{
	//std::cout << "values.size: " << values.size() << std::endl;
	if(values.size() > 0) return true;
	else return false;
}

std::string cLine::getOriginalLine()
{
	return originalLine;
}


unsigned int cLine::getAvgValue() const
{
	return avgValue;
}
unsigned int cLine::getNumValues() const
{
	return numValues;
}
unsigned int cLine::getMin() const
{
	return min;
}
unsigned int cLine::getMax() const
{
	return max;
}

std::vector<unsigned int> cLine::getValues() const
{
	return values;
}

cLine::~cLine()
{
}

