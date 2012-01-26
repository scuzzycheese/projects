/* 
 * File:   cParser.cpp
 * Author: scuzzy
 * 
 * Created on 26 January 2012, 11:30 PM
 */

#include "cParser.h"
#include <fstream>
#include <sstream>

#include <stdlib.h>

cParser::cParser()
{
}

cParser::cParser(std::string file)
{
	std::ifstream shapeFile;
	shapeFile.open(file.c_str());
	if(shapeFile.is_open())
	{
		while(shapeFile.good())
		{
			std::string sShape;
			std::getline(shapeFile, sShape);
			std::cout << sShape << " - ";

			std::istringstream ssShape(sShape);

			std::string name;

			if(ssShape.good()) { std::getline(ssShape, name, ','); }
			std::vector<int> coOrds;

			while(ssShape.good())
			{
				std::string token;
				std::getline(ssShape, token, ',');

				//for lack of a simpler way
				//TODO: find a better way
				coOrds.push_back(atoi(token.c_str()));

				std::cout << token << " ";
			}
			std::cout << std::endl;

			if(coOrds.size() == 4)
			{
				cRectangle rec(coOrds[0], coOrds[1], coOrds[2], coOrds[3]);
				rec.setName(name);
				shapes.push_back(rec);
			}
		}
		shapeFile.close();
	}
}

cParser::~cParser()
{
}

