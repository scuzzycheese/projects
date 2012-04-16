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
	cParseFromFile(std::string filename);
	virtual ~ cParseFromFile();
	std::vector<std::string> lines;
private:

};

#endif	/* _CPARSEFROMFILE_H */

