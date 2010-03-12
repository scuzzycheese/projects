#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <stdint.h>

#define DEFAULT_ALLOC_SIZE 1204


class cDStore
{

	char *dData;
	size_t dAllocSize;
	size_t dDataSize;

	public: 
	cDStore(size_t size) : dData(NULL), dAllocSize(0), dDataSize(0)
	{
		if(!(dData = new(std::nothrow) char[size]))
		{
			//NOTE: Do some error handling here
			//maybe throw and exception
		}
		else
		{
			dAllocSize = size;
		}
	}

	~cDStore()
	{
		delete[] dData;
	}

};


class cBuffer
{
	std::vector<cDStore> dChunks;
	size_t dNumChunks;

	public: 
	cBuffer();

	void copy(char *data,  size_t size)
	{
		cDStore *dstore = &(dChunks.front());
		if(dstore
	} 

};


#endif
