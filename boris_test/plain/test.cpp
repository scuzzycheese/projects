#include "cBuffer.h"
#include <stdio.h>

#include <stdlib.h>
#include <iostream>


int main()
{


	cBuffer buff(10, 3);

	buff.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	buff.append("hello there my good good friend,", strlen("hello there my good good friend,")); 
	buff.append(" how are you doing today?", strlen(" how are you doing today?"));

	buff.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	buff.append("moo", strlen("moo"));

	buff.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	buff.copy("woot12312", strlen("woot12312"));
	buff.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff.mNumChunks << std::endl;
	std::cout << "FINAL: " << buff.getBinary() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	

	char *moo = (char *)malloc(10);
	memcpy(moo, "1234567890", 10);
	cBuffer buff2(moo, 10, 20, true); 
	buff2.append("Test123", 7);

	buff2.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff2.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff2.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff2.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	buff2.capacity(100);
	buff2.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff2.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff2.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff2.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


}
