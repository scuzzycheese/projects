#include "cBuffer.h"
#include <stdio.h>

#include <stdlib.h>
#include <iostream>
#include <list>

struct testCase
{
	testCase(std::string name, bool pass) : mName(name), mPass(pass)
	{
	}

	std::string mName;
	bool mPass;
};

int main()
{

	std::list<testCase> tests;



	char *data = "This is a pretty good test";

	cBuffer buff1(3);
	buff1.copy(data, strlen(data)); 
	buff1.dumpBuffers();

	tests.push_back(testCase("Copy Test Chunks", buff1.mNumChunks == 2)); 


	
	buff1.append("this is kick ass", strlen("this is kick ass"));
	buff1.dumpBuffers();




	cBuffer buff(3);
	buff.dumpBuffers();

	buff.append("hello there my good good friend,", strlen("hello there my good good friend,")); 
	buff.append(" how are you doing today?", strlen(" how are you doing today?"));
	buff.dumpBuffers();


	buff.append("moo", strlen("moo"));
	buff.dumpBuffers();

	buff.copy("woot12312", strlen("woot12312"));
	buff.dumpBuffers();
	std::cout << "FINAL: " << buff.getBinary() << std::endl;

	
/*
	char *moo = (char *)malloc(10);
	memcpy(moo, "1234567890", 10);
	cBuffer buff2(moo, 10, 20, true); 
	buff2.append("Test123", 7);

	buff2.dumpBuffers();

	buff2.capacity(100);
	buff2.dumpBuffers();
*/


	for(std::list<testCase>::iterator i = tests.begin(), q = tests.end(); i != q; ++i)
	{
		std::cout << i->mName << ": " << (i->mPass ? "pass" : "fail") << std::endl;
	}

}
