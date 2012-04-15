#ifndef _CPARSEFROMFILE_H
#define	_CPARSEFROMFILE_H


#include <stdlib.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


class cParseFromFile
{
public:
	cParseFromFile();
	cParseFromFile(std::string filename);
	virtual ~ cParseFromFile();
private:
	std::vector<std::string> lines;

};

#endif	/* _CPARSEFROMFILE_H */

