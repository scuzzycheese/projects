#include "cBuffer.h"
#include "cBufferContig.h"
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
void testcBufferContig(std::list<testCase> &tests);

int main()
{
	std::list<testCase> tests;

	testcBuffer(tests);
	testcBufferContig(tests);

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

void testcBufferContig(std::list<testCase> &tests)
{
	char *data = "This is a pretty good test";
	cBufferContig buff1(3);
	buff1.copy(data, strlen(data)); 

	tests.push_back(testCase("cBufferContig Copy Test Buffer Size", buff1.mBufferSize == 26 + cBufferContig::DEFAULT_ALLOC_SIZE)); 
	tests.push_back(testCase("cBufferContig Copy Test Logical Buffer Size", buff1.getSize() == 26)); 
	tests.push_back(testCase("cBufferContig Copy Test getBinary", memcmp(buff1.getBinary(), "This is a pretty good test", 26) == 0));

	buff1.append("this is kick ass", strlen("this is kick ass"));

	tests.push_back(testCase("cBufferContig Append Test Logical Buffer Size", buff1.mLogicalSize == 42));
	tests.push_back(testCase("cBufferContig Append Test Buffer Size", buff1.mBufferSize == 42 + cBufferContig::DEFAULT_ALLOC_SIZE));
	tests.push_back(testCase("cBufferContig Append Test getBinary", memcmp(buff1.getBinary(), "This is a pretty good testthis is kick ass", 42) == 0));

	cBufferContig buff;
	
	tests.push_back(testCase("cBufferContig NoSize Test Logical Buffer Size", buff.mLogicalSize == 0));
	tests.push_back(testCase("cBufferContig NoSize Test Buffer Size", buff.mBufferSize == cBufferContig::DEFAULT_ALLOC_SIZE));

	buff.append("0123456789", 10); 

	tests.push_back(testCase("cBufferContig NoSize Test Logical Buffer Size 2", buff.mLogicalSize == 10));
	tests.push_back(testCase("cBufferContig NoSize Test Buffer Size 2", buff.mBufferSize == 10));

	buff.capacity(200);

	tests.push_back(testCase("cBufferContig Capacity Test Logical Buffer Size", buff.mLogicalSize == 10));
	tests.push_back(testCase("cBufferContig Capacity Test Buffer Size", buff.mBufferSize == 200));
	tests.push_back(testCase("cBufferContig Capacity Test getBinary", memcmp(buff.getBinary(), "0123456789", 10) == 0));

	buff.append("9876543210555", 13);

	tests.push_back(testCase("cBufferContig Capacity Append Test Logical Buffer Size", buff.mLogicalSize == 23));
	tests.push_back(testCase("cBufferContig Capacity Append Test Buffer Size", buff.mBufferSize == 200));
	tests.push_back(testCase("cBufferContig Capacity Test getBinary", memcmp(buff.getBinary(), "01234567899876543210555", 23) == 0));
	
	buff.copy("AAA", 3);

	tests.push_back(testCase("cBufferContig Capacity Copy Test Logical Buffer Size", buff.mLogicalSize == 23));
	tests.push_back(testCase("cBufferContig Capacity Copy Test Buffer Size", buff.mBufferSize == 200));
	tests.push_back(testCase("cBufferContig Capacity Copy Test getBinary 1", memcmp(buff.getBinary(), "AAA34567899876543210555", 23) == 0));
	
	buff.copy("AAaAaA", 6);
	
	tests.push_back(testCase("cBufferContig Capacity Copy Test getBinary 2", memcmp(buff.getBinary(), "AAaAaA67899876543210555", 23) == 0));

	buff.copy("00000000000000000000000", 23);

	tests.push_back(testCase("cBufferContig Capacity Copy Test getBinary 3", memcmp(buff.getBinary(), "00000000000000000000000", 23) == 0));

	buff.copy("0000000000000000000000000", 25);
	
	tests.push_back(testCase("cBufferContig Capacity Copy Test Logical Buffer Size 2", buff.mLogicalSize == 25));
	tests.push_back(testCase("cBufferContig Capacity Copy Test getBinary 3", memcmp(buff.getBinary(), "0000000000000000000000000", 25) == 0));

	try
	{
		cBufferContig buff2("hello", 5, 4);
		tests.push_back(testCase("cBufferContig Capacity failure test", false));
	}
	catch(std::exception &e)
	{
		tests.push_back(testCase("cBufferContig Capacity failure test", true));
	}

	char *allocData = new char[20];
	memcpy(allocData, "hello", 6);

	cBufferContig buff4(allocData, 6, 20, false);
	cBufferContig buff3(allocData, 6, 20, true);

	tests.push_back(testCase("cBufferContig Ownership Test buff4", buff4.mData != allocData));
	tests.push_back(testCase("cBufferContig Ownership Test buff3", buff3.mData == allocData));

	tests.push_back(testCase("cBufferContig Ownership Test Buffer compare buff4 before Alter", memcmp(buff4.mData, "hello", 6) == 0));
	tests.push_back(testCase("cBufferContig Ownership Test Buffer compare buff3 before Alter", memcmp(buff3.mData, "hello", 6) == 0));
	memcpy(allocData, "rah", 3);
	tests.push_back(testCase("cBufferContig Ownership Test Buffer compare buff4 after Alter", memcmp(buff4.mData, "hello", 6) == 0));
	tests.push_back(testCase("cBufferContig Ownership Test Buffer compare buff3 after Alter", memcmp(buff3.mData, "rahlo", 6) == 0));

	char *buff3Data = buff3.getBinary();
	char *buff4Data = buff4.getBinary();

	memcpy(buff3Data, "moo", 3);
	memcpy(buff4Data, "moo", 3);

	tests.push_back(testCase("cBufferContig Ownership Test Buffer compare getBinary buff4 after Alter", memcmp(buff4.mData, "moolo", 6) == 0));
	tests.push_back(testCase("cBufferContig Ownership Test Buffer compare getBinary buff3 after Alter", memcmp(buff3.mData, "moolo", 6) == 0));
	
	tests.push_back(testCase("cBufferContig Ownership Test Logical Buffer size", buff3.mLogicalSize == 6));
	tests.push_back(testCase("cBufferContig Ownership Test Buffer size", buff3.mBufferSize == 20));
}

void testcBuffer(std::list<testCase> &tests)
{
	char *data = "This is a pretty good test";
	cBuffer buff1(3);
	buff1.copy(data, strlen(data)); 
	buff1.dumpBuffers();

	tests.push_back(testCase("Copy Test Chunks", buff1.mNumChunks == 2)); 
	tests.push_back(testCase("Copy Test Buffer Size", buff1.mBufferSize == 26 + cBuffer::DEFAULT_ALLOC_SIZE)); 
	tests.push_back(testCase("Copy Test Logical Buffer Size", buff1.getSize() == 26)); 
	tests.push_back(testCase("Copy Test BuffChunk Data 1 size", buff1.mChunks[0]->mDataSize == 3));
	tests.push_back(testCase("Copy Test BuffChunk Allocation 1 size", buff1.mChunks[0]->mAllocSize == 3));
	tests.push_back(testCase("Copy Test BuffChunk Data 2 size", buff1.mChunks[1]->mDataSize == 23));
	tests.push_back(testCase("Copy Test BuffChunk Allocation 2 size", buff1.mChunks[1]->mAllocSize == 23 + cBuffer::DEFAULT_ALLOC_SIZE));
	tests.push_back(testCase("Copy Test getBinary", memcmp(buff1.getBinary(), "This is a pretty good test", 26) == 0));

	buff1.append("this is kick ass", strlen("this is kick ass"));
	buff1.dumpBuffers();

	tests.push_back(testCase("Append Test Logical Buffer Size", buff1.mLogicalSize == 42));
	tests.push_back(testCase("Append Test Buffer Size", buff1.mBufferSize == 42 + cBuffer::DEFAULT_ALLOC_SIZE));
	tests.push_back(testCase("Append Test Chunks", buff1.mNumChunks == 3));
	tests.push_back(testCase("Append Test BuffChunk Data 2 size", buff1.mChunks[1]->mDataSize == 33));
	tests.push_back(testCase("Append Test BuffChunk Allocation 2 size", buff1.mChunks[1]->mAllocSize == 33));
	tests.push_back(testCase("Append Test BuffChunk Data 3 size", buff1.mChunks[2]->mDataSize == 6));
	tests.push_back(testCase("Append Test BuffChunk Allocation 3 size", buff1.mChunks[2]->mAllocSize == 16));
	tests.push_back(testCase("Append Test getBinary", memcmp(buff1.getBinary(), "This is a pretty good testthis is kick ass", 42) == 0));

	cBuffer buff;
	buff.dumpBuffers();
	
	tests.push_back(testCase("NoSize Test Logical Buffer Size", buff.mLogicalSize == 0));
	tests.push_back(testCase("NoSize Test Buffer Size", buff.mBufferSize == cBuffer::DEFAULT_ALLOC_SIZE));
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

	cBuffer buff5("hello", 5);

	tests.push_back(testCase("copy in with constructor Logical Buffer size", buff5.mLogicalSize == 5));
	tests.push_back(testCase("copy in with constructor Buffer size", buff5.mBufferSize == 5));
	tests.push_back(testCase("copy in with constructor number chunks", buff5.mNumChunks == 1));
	tests.push_back(testCase("copy in with constructor chunk data size", buff5.mChunks[0]->mDataSize == 5));
	tests.push_back(testCase("copy in with constructor chunk allocation size", buff5.mChunks[0]->mAllocSize == 5));



}
