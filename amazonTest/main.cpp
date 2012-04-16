#include "cParseFromFile.h"
#include "cLine.h"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout << "Usage: ./amLines <file>" << std::endl;
		exit(EXIT_FAILURE);
	}

	cParseFromFile parser(argv[1]);

	for(std::vector<std::string>::iterator i = parser.lines.begin(); i < parser.lines.end(); i ++)
	{
		cLine line(*i);
		if(line.validLine())
		{
			std::cout << "ORIGIN: " << line.getOriginalLine() << std::endl;
			std::cout << "MAX: " << line.getMax() << std::endl;
			std::cout << "MIN: " << line.getMin() << std::endl;
			std::cout << "AVG: " << line.getAvgValue() << std::endl << std::endl;
		}
	}

}
