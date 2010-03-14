#include "cDStore.h"


cDStore::cDStore(const size_t &size) throw(std::bad_alloc) : mData(NULL), mAt(NULL), mAllocSize(0), mDataSize(0)
{
#ifdef BUFF_DEBUG
	mData = new char[size + sizeof(uint32_t)];
	*((uint32_t *)(mData + size)) = 0xDEADBEEF;
#else
	mData = new char[size];
#endif
	mAllocSize = size;
	mAt = mData;
}



cDStore::cDStore(const size_t &size, char * const &data, bool takeOwnership) throw(std::bad_alloc) : mData(NULL), mAt(NULL), mAllocSize(0), mDataSize(0)
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
		mData = new char[size + sizeof(uint32_t)];
		*((uint32_t *)(mData + size)) = 0xDEADBEEF;
#else
		mData = new char[size];
#endif
		mAllocSize = size;
		mAt = mData;
		memcpy(mAt, data, size);
		mAt += size;
	}
}

cDStore::~cDStore()
{
	delete[] mData;
}


size_t cDStore::mSpaceLeft()
{
	return mAllocSize - mDataSize;
}


/**
 * Test this method for edge cases
 * eg: where mDataSize and size are
 * the same
 */
void cDStore::copy(char * const &data, const size_t &size) throw(bad_capacity)
{
	if(size <= mAllocSize)
	{
		memcpy(mData, data, size);
		mAt += (mDataSize < size) ? size - mDataSize : 0;
		mDataSize += (mDataSize < size) ? size - mDataSize : 0;
	}
	else
	{
		throw bad_capacity("block does not have enough space");
	}
#ifdef BUFF_DEBUG
	assert(*((uint32_t *)(mData + mAllocSize)) == 0xDEADBEEF);
#endif
	
}


void cDStore::append(char * const &data, const size_t &size) throw(bad_capacity)
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
		throw bad_capacity("block does not have enough space");
	}
#ifdef BUFF_DEBUG
	assert(*((uint32_t *)(mData + mAllocSize)) == 0xDEADBEEF);
#endif
}

