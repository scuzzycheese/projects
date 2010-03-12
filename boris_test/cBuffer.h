#ifndef CBUFFER_H
#define CBUFFER_H

#include "cBufferBase.h"

#include <vector>
#include <stdint.h>
#include <string.h>



class cDStore
{

	char *mData;
	char *mAt;
	size_t mAllocSize;
	size_t mDataSize;

	public: 
	cDStore(size_t size) : mData(NULL), mAt(NULL), mAllocSize(0), mDataSize(0)
	{
		if(!(mData = new(std::nothrow) char[size]))
		{
			//NOTE: Do some error handling here
			//maybe throw and exception
		}
		else
		{
			mAllocSize = size;
			mAt = mData;
		}
	}


	~cDStore()
	{
		delete[] mData;
	}

	size_t mSpaceLeft()
	{
		return mAllocSize - mDataSize;
	}

	void append(char *&data, size_t &size)
	{
		//NOTE: maybe optimise this if statement
		if(mSpaceLeft() > 0 && size <= mSpaceLeft())
		{
			memcpy(mData, data, size);
			mAt += size;
			mDataSize += size;
		}
		else
		{
			//NOTE: maybe throw an exception, or return 0?
		}
	}

	char *getData()
	{
		return mData;
	}


};


class cBuffer
{
	std::vector<cDStore *> dChunks;
	size_t dNumChunks;

	public: 
	cBuffer();
	~cBuffer();

	void copy(char *data, size_t size);
	void append(char *date, size_t size);
	void capacity(size_t size);
	
	char *currentBuffer();

	void allocateInternalBuffer(size_t size);
	void copyToInternalBuffer(char *data, size_t size);
	void appendToInternalBuffer(char *data, size_t size);
	void setInternalCapacity(size_t size);

};


#endif

