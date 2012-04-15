#include "cParseFromFile.h"
#include "cLine.h"

int main(int argc, char **argv)
{

	cParseFromFile parser("lines");

	for(std::vector<std::string>::iterator i = parser.lines.begin(); i < parser.lines.end(); i ++)
	{
		cLine line(*i);
	}

}
