#include "cBuffer.h"
#include <stdio.h>

#include <stdlib.h>
#include <iostream>


int main()
{


	cBuffer buff(10, 57);

	buff.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	buff.copy("hello there my good good friend,", strlen("hello there my good good friend,")); 
	buff.copy(" how are you doing today?", strlen(" how are you doing today?"));

	buff.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	buff.copy("moo", strlen("moo"));

	buff.dumpBuffers();
	std::cout << "BUFFSIZE: " << buff.mBufferSize << std::endl;
	std::cout << "LOGICALSIZE: " << buff.mLogicalSize << std::endl;
	std::cout << "NUMBER OF CHUNKS: " << buff.mNumChunks << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

}
