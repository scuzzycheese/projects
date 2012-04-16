#include "cLine.h"
#include <sstream>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>


cLine::cLine()
{
}

cLine::cLine(std::string line) : min(0), max(0), numValues(0)
{
	std::istringstream ssLine(line);
	long long totalValue = 0;
	while(ssLine.good())
	{
		char *endptr;
		std::string token;
		std::getline(ssLine, token, ' ');

		//TODO: Add error checking here
		errno = 0;
		int intVal = strtol(token.c_str(), &endptr, 10);
      if(errno == ERANGE && (intVal == LONG_MAX || intVal == LONG_MIN))
		{
			std::cout << "Bad Value(leaving out of set): " << token << std::flush;
			perror(" ");
		}
		else if(intVal < 0)
		{
			std::cout << "Bad Value(leaving out of set): " << token << " : Negative number" << std::endl;
		}
		else
		{
			if(intVal >= 0)
			{
				if(intVal < min) min = intVal;
				if(intVal > max) max = intVal;
				numValues ++;
				totalValue += intVal;
				values.push_back(intVal);
			}
		}

	}
	if(totalValue > 0 && numValues > 0) avgValue = totalValue / numValues;
}

cLine::~cLine()
{
}

