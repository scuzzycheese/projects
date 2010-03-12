#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <stdint.h>

#define DEFAULT_ALLOC_SIZE 1204


class cDStore
{

	char *dData;
	uint32_t dAllocSize;
	uint32_t dDataSize;

	public: 
	/**
	 * dAllocSize should maybe be initialised after the new
	 * because we want to make sure the allocation doesn't
	 * faile
	 */
	cDStore(uint32_t size) : dData(NULL), dAllocSize(size), dDataSize(0)
	{
		if(!(dData = new(std::nothrow) char[size]))
		{
			//Do some error handling here
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
	uint16_t dNumChunks;

	public: 
	cBuffer();

};


#endif
