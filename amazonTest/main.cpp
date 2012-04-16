#include "cParseFromFile.h"
#include "cLine.h"

int main(int argc, char **argv)
{

	cParseFromFile parser("lines");

	for(std::vector<std::string>::iterator i = parser.lines.begin(); i < parser.lines.end(); i ++)
	{
		cLine line(*i);
		if(line.validLine())
		{
			std::cout << "ORIGIN: " << line.origin() << std::endl;
			std::cout << "MAX: " << line.max << std::endl;
			std::cout << "MIN: " << line.min << std::endl;
			std::cout << "AVG: " << line.avgValue << std::endl << std::endl;
		}
	}

}
