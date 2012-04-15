#include "cLine.h"
#include <sstream>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>


cLine::cLine()
{
}

cLine::cLine(std::string line)
{
	std::istringstream ssLine(line);
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
				values.push_back(intVal);
				std::cout << intVal << " ";
			}
		}

	}
	std::cout << std::endl;
}

cLine::~cLine()
{
}

