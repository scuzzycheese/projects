#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <iostream>
#include <stdint.h>
#include <string.h>

#define DEFAULT_ALLOC_SIZE 10



class cDStore
{
	friend class cBuffer;

	char *mData;
	char *mAt;
	size_t mAllocSize;
	size_t mDataSize;

	public: 
	cDStore(const size_t &size) : mData(NULL), mAt(NULL), mAllocSize(0), mDataSize(0)
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

	
	cDStore(const size_t &size, char * const &data, bool takeOwnership = false) : mData(NULL), mAt(NULL), mAllocSize(0), mDataSize(0)
	{
		if(takeOwnership)
		{
			mData = data;
			mAllocSize = size;
			mDataSize = size;
			mAt = mData;
		}
		else
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
				memcpy(mAt, data, size);
				mAt += size;
			}
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

	void copy(char * const &data, const size_t &size)
	{
		if(size <= mAllocSize)
		{
			memcpy(mData, data, size);
			mAt += size;
			mDataSize += size;
		}
		else
		{
			std::cout << "=======================EXCEPTION: Either block does not have sufficient space" << std::endl;
			//NOTE: maybe throw an exception
		}
	}

	void append(char * const &data, const size_t &size)
	{
		//NOTE: maybe optimise this if statement
		if(mSpaceLeft() > 0 && size <= mSpaceLeft())
		{
			memcpy(mAt, data, size);
			mAt += size;
			mDataSize += size;
		}
		else
		{
			
			std::cout << "=======================EXCEPTION: Either block has no space left, or requested space is not sufficient" << std::endl;
			//NOTE: maybe throw an exception, or return 0?
		}
	}

};


class cBuffer
{
	std::vector<cDStore *> mChunks;

	//note, this is just for debugging, should be private
	public:
	size_t mNumChunks;
	size_t mBufferSize;
	size_t mLogicalSize;
	char *mBinaryP;

	void expandBy(const size_t &size);
	public: 

	cBuffer();
	cBuffer(const size_t &size);
	cBuffer(char * const &data, const size_t &size);
	cBuffer(char * const &data, const size_t &size, const size_t &growToWithoutRealloc, bool takeOwnership = false);

	~cBuffer();

	void copy(char *data, size_t size);
	void append(char *date, size_t size);
	void capacity(const size_t &size);

	char *getBinary();
	
	void dumpBuffers();
};


#endif

