#include "cBuffer.h"
#include <stdio.h>

#include <stdlib.h>
#include <iostream>
#include <list>

struct testCase
{
	testCase(const std::string &name, const bool &pass) : mName(name), mPass(pass)
	{
	}

	std::string mName;
	bool mPass;
};

void testcBuffer(std::list<testCase> &tests);

int main()
{
	std::list<testCase> tests;

	testcBuffer(tests);

	uint16_t passes = 0;
	for(std::list<testCase>::iterator i = tests.begin(), q = tests.end(); i != q; ++i)
	{
		std::cout << i->mName << ": ";
		if(i->mPass)
		{
			std::cout << "pass";
			++ passes;
		}
		else
		{
			std::cout << "fail";
		}
		std::cout << std::endl;
	}
	std::cout << "Tests Pass Rate: ";
	std::cout << passes << "/" << tests.size() << std::endl;
}


void testcBuffer(std::list<testCase> &tests)
{
	char *data = "This is a pretty good test";
	cBuffer buff1(3);
	buff1.copy(data, strlen(data)); 
	buff1.dumpBuffers();

	tests.push_back(testCase("Copy Test Chunks", buff1.mNumChunks == 2)); 
	tests.push_back(testCase("Copy Test Buffer Size", buff1.mBufferSize == 26 + DEFAULT_ALLOC_SIZE)); 
	tests.push_back(testCase("Copy Test Logical Buffer Size", buff1.mLogicalSize == 26)); 
	tests.push_back(testCase("Copy Test BuffChunk Data 1 size", buff1.mChunks[0]->mDataSize == 3));
	tests.push_back(testCase("Copy Test BuffChunk Allocation 1 size", buff1.mChunks[0]->mAllocSize == 3));
	tests.push_back(testCase("Copy Test BuffChunk Data 2 size", buff1.mChunks[1]->mDataSize == 23));
	tests.push_back(testCase("Copy Test BuffChunk Allocation 2 size", buff1.mChunks[1]->mAllocSize == 23 + DEFAULT_ALLOC_SIZE));
	tests.push_back(testCase("Copy Test getBinary", memcmp(buff1.getBinary(), "This is a pretty good test", 26) == 0));

	buff1.append("this is kick ass", strlen("this is kick ass"));
	buff1.dumpBuffers();

	tests.push_back(testCase("Append Test Logical Buffer Size", buff1.mLogicalSize == 42));
	tests.push_back(testCase("Append Test Buffer Size", buff1.mBufferSize == 42 + DEFAULT_ALLOC_SIZE));
	tests.push_back(testCase("Append Test Chunks", buff1.mNumChunks == 3));
	tests.push_back(testCase("Append Test BuffChunk Data 2 size", buff1.mChunks[1]->mDataSize == 33));
	tests.push_back(testCase("Append Test BuffChunk Allocation 2 size", buff1.mChunks[1]->mAllocSize == 33));
	tests.push_back(testCase("Append Test BuffChunk Data 3 size", buff1.mChunks[2]->mDataSize == 6));
	tests.push_back(testCase("Append Test BuffChunk Allocation 3 size", buff1.mChunks[2]->mAllocSize == 16));
	tests.push_back(testCase("Append Test getBinary", memcmp(buff1.getBinary(), "This is a pretty good testthis is kick ass", 42) == 0));

	cBuffer buff;
	buff.dumpBuffers();
	
	tests.push_back(testCase("NoSize Test Logical Buffer Size", buff.mLogicalSize == 0));
	tests.push_back(testCase("NoSize Test Buffer Size", buff.mBufferSize == DEFAULT_ALLOC_SIZE));
	tests.push_back(testCase("NoSize Test Chunks", buff.mNumChunks == 1));

	buff.append("0123456789", 10); 

	tests.push_back(testCase("NoSize Test Logical Buffer Size 2", buff.mLogicalSize == 10));
	tests.push_back(testCase("NoSize Test Buffer Size 2", buff.mBufferSize == 10));
	tests.push_back(testCase("NoSize Test Chunks 2", buff.mNumChunks == 1));

	buff.capacity(200);

	tests.push_back(testCase("Capacity Test Chunks", buff.mNumChunks == 2));
	tests.push_back(testCase("Capacity Test Logical Buffer Size", buff.mLogicalSize == 10));
	tests.push_back(testCase("Capacity Test Buffer Size", buff.mBufferSize == 200));
	tests.push_back(testCase("Capacity Test getBinary", memcmp(buff.getBinary(), "0123456789", 10) == 0));

	buff.append("9876543210555", 13);

	tests.push_back(testCase("Capacity Append Test Chunks", buff.mNumChunks == 2));
	tests.push_back(testCase("Capacity Append Test Logical Buffer Size", buff.mLogicalSize == 23));
	tests.push_back(testCase("Capacity Append Test Buffer Size", buff.mBufferSize == 200));
	tests.push_back(testCase("Capacity Test getBinary", memcmp(buff.getBinary(), "01234567899876543210555", 23) == 0));
	
	buff.copy("AAA", 3);

	tests.push_back(testCase("Capacity Copy Test Chunks", buff.mNumChunks == 2));
	tests.push_back(testCase("Capacity Copy Test Logical Buffer Size", buff.mLogicalSize == 23));
	tests.push_back(testCase("Capacity Copy Test Buffer Size", buff.mBufferSize == 200));
	tests.push_back(testCase("Capacity Copy Test getBinary 1", memcmp(buff.getBinary(), "AAA34567899876543210555", 23) == 0));
	
	buff.copy("AAaAaA", 6);
	
	tests.push_back(testCase("Capacity Copy Test getBinary 2", memcmp(buff.getBinary(), "AAaAaA67899876543210555", 23) == 0));

	buff.copy("00000000000000000000000", 23);

	tests.push_back(testCase("Capacity Copy Test getBinary 3", memcmp(buff.getBinary(), "00000000000000000000000", 23) == 0));

	buff.copy("0000000000000000000000000", 25);
	
	tests.push_back(testCase("Capacity Copy Test Chunks 2", buff.mNumChunks == 2));
	tests.push_back(testCase("Capacity Copy Test Logical Buffer Size 2", buff.mLogicalSize == 25));
	tests.push_back(testCase("Capacity Copy Test getBinary 3", memcmp(buff.getBinary(), "0000000000000000000000000", 25) == 0));

	try
	{
		cBuffer buff2("hello", 5, 4);
		tests.push_back(testCase("Capacity failure test", false));
	}
	catch(std::exception &e)
	{
		tests.push_back(testCase("Capacity failure test", true));
	}

	char *allocData = new char[20];
	memcpy(allocData, "hello", 6);
	cBuffer buff3(allocData, 6, 20, true);

	tests.push_back(testCase("Ownership Test 1", buff3.mChunks[0]->mData == allocData));
	tests.push_back(testCase("Ownership Test Logical Buffer size", buff3.mLogicalSize == 6));
	tests.push_back(testCase("Ownership Test Buffer size", buff3.mBufferSize == 20));
	tests.push_back(testCase("Ownership Test Block 0 size",  buff3.mChunks[0]->mDataSize == 6));
	tests.push_back(testCase("Ownership Test Block 0 Alloc size",  buff3.mChunks[0]->mAllocSize == 6));
	tests.push_back(testCase("Ownership Test Block 1 size",  buff3.mChunks[1]->mDataSize == 0));
	tests.push_back(testCase("Ownership Test Block 1 Alloc size",  buff3.mChunks[1]->mAllocSize == 14));

}
