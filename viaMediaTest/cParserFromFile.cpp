/* 
 * File:   cParser.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 11:30 PM
 */

#include "cParserFromFile.h"
#include <fstream>
#include <sstream>

#include <stdlib.h>

cParseFromFile::cParseFromFile()
{
}

cParseFromFile::cParseFromFile(std::string file) : cParse()
{
	parse(file);
}

std::vector<cLineRep> cParseFromFile::fetchLines()
{
	return lines;
}

void cParseFromFile::parse(std::string file)
{
	std::ifstream shapeFile;
	shapeFile.open(file.c_str());
	if(shapeFile.is_open())
	{
		while(shapeFile.good())
		{
			std::string sShape;
			std::getline(shapeFile, sShape);

			std::istringstream ssShape(sShape);

			std::string name;
			if(ssShape.good()) { std::getline(ssShape, name, ','); }

			cLineRep newLine(name);

			while(ssShape.good())
			{
				std::string token;
				std::getline(ssShape, token, ',');

				//for lack of a simpler way
				//TODO: find a better way
				newLine.addValue(atoi(token.c_str()));
			}
			lines.push_back(newLine);
		}
		shapeFile.close();
	}
}

cParseFromFile::~cParseFromFile()
{
}

