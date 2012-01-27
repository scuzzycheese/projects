#include <iostream>

#include <fstream>
#include <sstream>
#include "cParserFromFile.h"
#include "cRectangle.h"

int main()
{

	cParseFromFile par("shapes.txt");
	std::vector<cShape *> shapes;
	std::vector<cLineRep> lines = par.fetchLines();
	for(std::vector<cLineRep>::iterator linIt = lines.begin(); linIt < lines.end(); linIt ++)
	{
		cShape *shape = new cShape(*linIt);
		shapes.push_back(shape);
	}
	for(std::vector<cShape *>::iterator shapeIt = shapes.begin(); shapeIt < shapes.end(); shapeIt ++)
	{
		cRectangle *rec = (cRectangle *)*shapeIt;
		std::cout << rec->getName() << "-" << std::endl;
		for(std::vector<cShape *>::iterator shapeTest = shapes.begin(); shapeTest < shapes.end(); shapeTest ++)
		{
			cRectangle *recTest = (cRectangle *)*shapeTest;
			if(rec != recTest)
			{
				if(rec->collide(*recTest))
				{
					std::cout << recTest->getName() << std::endl;
				}
				if(rec->contains(*recTest))
				{
					std::cout << recTest->getName() << std::endl;
				}
				if(rec->touches(*recTest))
				{
					std::cout << recTest->getName() << std::endl;
				}
			}
		}
		std::cout << std::endl;
	}


}
