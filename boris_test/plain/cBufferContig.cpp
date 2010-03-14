#include "cBufferContig.h"


cBufferContig::cBufferContig() : mData(NULL), mBufferSize(0), mLogicalSize(0)
{
	expandBy(DEFAULT_ALLOC_SIZE);
}


cBufferContig::cBufferContig(const size_t &size) : mData(NULL), mBufferSize(0), mLogicalSize(0)
{
	expandBy(size);
}

cBufferContig::cBufferContig(char * const &data, const size_t &size) : mData(NULL), mBufferSize(0), mLogicalSize(size)
{
	expandBy(size);
	memcpy(mData, data, size);
}

cBufferContig::cBufferContig(char *&data, const size_t &size, const size_t &capacity, bool takeOwnership) : mData(NULL), mBufferSize(0), mLogicalSize(size)
{
	if(capacity < size)
	{
		throw bad_capacity("capacity does not exceed space");
	}

	if(takeOwnership)
	{
		reAlloc(data, size, capacity);
		mData = data;
		mBufferSize += capacity;
	}
	else
	{
		expandBy(capacity);
		memcpy(mData, data, size);
	}

}

cBufferContig::cBufferContig(char * const &data, const size_t &size, const size_t &capacity) : mData(NULL), mBufferSize(0), mLogicalSize(size)
{
	if(capacity < size)
	{
		throw bad_capacity("capacity does not exceed space");
	}
	
	expandBy(capacity);
	memcpy(mData, data, size);
}


cBufferContig::~cBufferContig()
{
	delete[] mData;
}

void cBufferContig::copy(char *data, size_t size) throw(std::bad_alloc)
{
	if(size > mBufferSize)
	{
		expandBy((size - mBufferSize) + DEFAULT_ALLOC_SIZE);
		memcpy(mData, data, size);
		mLogicalSize = size;
	}
	else
	{
		memcpy(mData, data, size);
		if(size > mLogicalSize) mLogicalSize = size;
	}
}

void cBufferContig::append(char *data, size_t size) throw(std::bad_alloc)
{
	if(mBufferSize < (mLogicalSize + size))
	{
		expandBy(((mLogicalSize + size) - mBufferSize) + DEFAULT_ALLOC_SIZE);
		memcpy(mData + mLogicalSize, data, size);
		mLogicalSize += size;
	}
	else
	{
		memcpy(mData + mLogicalSize, data, size);
		mLogicalSize += size;
	}
}


void cBufferContig::capacity(const size_t &size) throw(std::bad_alloc)
{
	if(mBufferSize < size)
	{
		expandBy(size - mBufferSize);
	}
}


char *cBufferContig::getBinary()
{
	return mData;
}



void cBufferContig::expandBy(const size_t &size)
{
	if(mData)
	{
		reAlloc(mData, mLogicalSize, mBufferSize + size);
		mBufferSize += size;
	}
	else mData = new char[size];
}

void cBufferContig::reAlloc(char *&data, const size_t &oldSize, const size_t &newSize)
{
	if(newSize > oldSize)
	{
		char *newData = new char[newSize];
		memcpy(newData, data, oldSize);
		delete[] data;
		data = newData;
	}
	else
	{
		//EXCEPTION: Maybe throw a bad_capacity exception
	}
}
