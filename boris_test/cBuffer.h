#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <stdint.h>
#include <string.h>

#define DEFAULT_ALLOC_SIZE 1204


class cDStore
{

	char *dData;
	char *dAt;
	size_t dAllocSize;
	size_t dDataSize;

	public: 
	cDStore(size_t size) : dData(NULL), dAt(NULL), dAllocSize(0), dDataSize(0)
	{
		if(!(dData = new(std::nothrow) char[size]))
		{
			//NOTE: Do some error handling here
			//maybe throw and exception
		}
		else
		{
			dAllocSize = size;
			dAt = dData;
		}
	}


	~cDStore()
	{
		delete[] dData;
	}

	size_t mSpaceLeft()
	{
		return dAllocSize - dDataSize;
	}

	void mAppend(char *&data, size_t &size)
	{
		//NOTE: maybe optimise this if statement
		if(mSpaceLeft() > 0 && size <= mSpaceLeft())
		{
			memcpy(dData, data, size);
			dAt += size;
		}
		else
		{
			//NOTE: maybe throw an exception, or return 0?
		}
	}


};


class cBuffer
{
	std::vector<cDStore *> dChunks;
	size_t dNumChunks;

	public: 
	cBuffer();
	~cBuffer();

	void copy(char *data,  size_t &size);

};


#endif
