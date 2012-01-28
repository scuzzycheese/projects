#include <iostream>

#include <fstream>
#include <sstream>
#include "cParserFromFile.h"
#include "cRectangle.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout << "Usage: ./lapper <rectangle file>" << std::endl;
		exit(EXIT_FAILURE);
	}

	cParseFromFile par(argv[1]);
	std::vector<cShape *> shapes;
	std::vector<cLineRep> lines = par.fetchLines();
	for(std::vector<cLineRep>::iterator linIt = lines.begin(); linIt < lines.end(); linIt ++)
	{
		cShape *shape = new cRectangle;
		shape->buildFromLineRep(*linIt);
		shapes.push_back(shape);
	}
	for(std::vector<cShape *>::iterator shapeIt = shapes.begin(); shapeIt < shapes.end(); shapeIt ++)
	{
		cRectangle *rec = (cRectangle *)*shapeIt;
		for(std::vector<cShape *>::iterator shapeTest = shapes.begin(); shapeTest < shapes.end(); shapeTest ++)
		{
			cRectangle *recTest = (cRectangle *)*shapeTest;
			if(rec != recTest)
			{
				rec->collide(*recTest);
				rec->contains(*recTest);
				rec->touches(*recTest);
			}
		}
	}
	for(std::vector<cShape *>::iterator shapeIt = shapes.begin(); shapeIt < shapes.end(); shapeIt ++)
	{
		cRectangle *rec = (cRectangle *)*shapeIt;
		std::cout << rec->getName() << std::endl;

		if(rec->mCollidesWith.size() > 0)
		{
			for(std::map<std::string, cShape *>::iterator conIt = rec->mCollidesWith.begin(); conIt != rec->mCollidesWith.end();)
			{
				std::cout << (*conIt).second->getName();
				if(++ conIt != rec->mCollidesWith.end()) std::cout << ",";
			}
		}
		else std::cout << "0";
		std::cout << std::endl;

		if(rec->mContains.size() > 0)
		{
			for(std::map<std::string, cShape *>::iterator conIt = rec->mContains.begin(); conIt != rec->mContains.end();)
			{
				std::cout << (*conIt).second->getName();
				if(++ conIt != rec->mContains.end()) std::cout << ",";
			}
		}
		else std::cout << "0";
		std::cout << std::endl;

		if(rec->mContainedBy.size() > 0)
		{
			for(std::map<std::string, cShape *>::iterator conIt = rec->mContainedBy.begin(); conIt != rec->mContainedBy.end();)
			{
				std::cout << (*conIt).second->getName();
				if(++ conIt != rec->mContainedBy.end()) std::cout << ",";
			}
		}
		else std::cout << "0";
		std::cout << std::endl;

		if(rec->mTouches.size() > 0)
		{
			for(std::map<std::string, cShape *>::iterator conIt = rec->mTouches.begin(); conIt != rec->mTouches.end();)
			{
				std::cout << (*conIt).second->getName();
				if(++ conIt != rec->mTouches.end()) std::cout << ",";
			}
		}
		else std::cout << "0";
		std::cout << std::endl;

		std::cout << std::endl;
		delete(*shapeIt);
	}


}
