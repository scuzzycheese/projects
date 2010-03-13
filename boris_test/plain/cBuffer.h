#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define DEFAULT_ALLOC_SIZE 10



class cDStore
{
	friend class cBuffer;

#ifdef BUFF_DEBUG
	public:
#endif
	char *mData;
	char *mAt;
	size_t mAllocSize;
	size_t mDataSize;


	public: 
	/**
	 * Creates a cDStore allocation block of a given size
	 *
	 * @param[in] size allocate a block of <size>
	 */
	cDStore(const size_t &size) throw(std::bad_alloc) : mData(NULL), mAt(NULL), mAllocSize(0), mDataSize(0)
	{
#ifdef BUFF_DEBUG
		mData = new(std::nothrow) char[size + sizeof(uint32_t)];
		*((uint32_t *)(mData + size)) = 0xDEADBEEF;
#else
		mData = new(std::nothrow) char[size];
#endif
		mAllocSize = size;
		mAt = mData;
	}

	/**
	 * Creates a cDStore allocation block of given size and pass in data
	 *
	 * Creates a cDStore allocation block of a given size and copies
	 * data into it. If takeOwnership is specified, then the block
	 * assume ownership of the data, and uses size as a basis for it's
	 * size
	 *
	 * @param[in] size allocate a block of <size> or use this as the size of data
	 * @param[in] data the data to be copied/owned
	 * @param[in] takeOwnership ownership flag for data
	 */
	cDStore(const size_t &size, char * const &data, bool takeOwnership = false) throw(std::bad_alloc) : mData(NULL), mAt(NULL), mAllocSize(0), mDataSize(0)
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
#ifdef BUFF_DEBUG
			mData = new(std::nothrow) char[size + sizeof(uint32_t)];
			*((uint32_t *)(mData + size)) = 0xDEADBEEF;
#else
			mData = new(std::nothrow) char[size];
#endif
			mAllocSize = size;
			mAt = mData;
			memcpy(mAt, data, size);
			mAt += size;
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

	/**
	 * Test this method for edge cases
	 * eg: where mDataSize and size are
	 * the same
	 */
	/**
	 * Copy data into the beginning of the block
	 *
	 * @param[in] data Data to be copied
	 * @param[in] size Size of the data to be copied
	 */
	void copy(char * const &data, const size_t &size)
	{
		if(size <= mAllocSize)
		{
			memcpy(mData, data, size);
			mAt += (mDataSize < size) ? size - mDataSize : 0;
			mDataSize += (mDataSize < size) ? size - mDataSize : 0;
		}
		else
		{
			std::cout << "=======================EXCEPTION: Either block does not have sufficient space" << std::endl;
			//NOTE: maybe throw an exception
		}
#ifdef BUFF_DEBUG
		assert(*((uint32_t *)(mData + mAllocSize)) == 0xDEADBEEF);
#endif
		
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
#ifdef BUFF_DEBUG
		assert(*((uint32_t *)(mData + mAllocSize)) == 0xDEADBEEF);
#endif
	}

};


class cBuffer
{

#ifdef BUFF_DEBUG
	public:
#endif
	std::vector<cDStore *> mChunks;
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

