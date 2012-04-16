#include "cParseFromFile.h"

cParseFromFile::cParseFromFile(std::string filename)
{
   std::ifstream lineFile;
   lineFile.open(filename.c_str());
   if(lineFile.is_open())
   {
      while(lineFile.good())
      {
         std::string line;
         std::getline(lineFile, line);
			lines.push_back(line);
		}
		lineFile.close();
	}
}

cParseFromFile::~cParseFromFile()
{
}

