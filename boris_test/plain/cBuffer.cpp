#include "cBuffer.h"


cBuffer::cBuffer() : mNumChunks(1), mBufferSize(DEFAULT_ALLOC_SIZE), mLogicalSize(0), mBinaryP(NULL)
{
	/**
	 * NOTE: catch an exception here (allocation
	 * failure)
	 */
	mChunks.push_back(new cDStore(DEFAULT_ALLOC_SIZE));
}

cBuffer::cBuffer(const size_t &size) : mNumChunks(1), mBufferSize(size), mLogicalSize(0), mBinaryP(NULL)
{
	mChunks.push_back(new cDStore(size));
}

cBuffer::cBuffer(const size_t &size, const size_t &capacity) : mNumChunks(1), mBufferSize(capacity), mLogicalSize(0), mBinaryP(NULL)
{
	mChunks.push_back(new cDStore(capacity));
}

cBuffer::cBuffer(char * const &data, const size_t &size) : mNumChunks(1), mBufferSize(size), mLogicalSize(size), mBinaryP(NULL)
{
	mChunks.push_back(new cDStore(size, data));
}

cBuffer::cBuffer(char * const &data, const size_t &size, const size_t &capacity, bool takeOwnership) : mNumChunks(1), mBufferSize(capacity), mLogicalSize(size), mBinaryP(NULL)
{
	if(capacity < size)
	{
		//Throw an exception
		std::cout << "EXCEPTION: capacity does not exceed space" << std::endl;
	}
	mChunks.push_back(new cDStore(size, data, takeOwnership));
	if(capacity > size)
	{
		//I don't know is this is the desired behavior, maybe.
		mChunks.push_back(new cDStore(capacity - size));
		mNumChunks = 2;
	}
}


cBuffer::~cBuffer()
{
	for(std::vector<cDStore *>::iterator i = mChunks.begin(), q = mChunks.end(); i != q; ++i)
	{
		delete(*i);
	}
	if(mBinaryP)
	{
		delete[] mBinaryP;
		mBinaryP = NULL;
	}
	
}


void cBuffer::expandBy(const size_t &size)
{
	mChunks.push_back(new cDStore(size));
	++ mNumChunks;
	mBufferSize += size;
}

void cBuffer::copy(char *data, size_t size)
{
	if(size > mBufferSize)
	{
		expandBy(size - mBufferSize);
	}

	for(std::vector<cDStore *>::iterator i = mChunks.begin(), q = mChunks.end(); i != q; ++i)
	{
		if(size < (*i)->getAllocSize())
		{
			(*i)->copy(data, size);
			return;
		}
		else
		{
			(*i)->copy(data, (*i)->getAllocSize());
			size -= (*i)->getAllocSize();
			data += (*i)->getAllocSize();
		}
	}
}

void cBuffer::append(char *data, size_t size)
{
	cDStore *dstore = mChunks.back();
	size_t spaceLeft = dstore->mSpaceLeft();

	if(spaceLeft >= size)
	{
		dstore->append(data, size);
		mLogicalSize += size;
	}
	else
	{
		if(spaceLeft > 0)
		{
			dstore->append(data, spaceLeft);
			data += spaceLeft;
			mLogicalSize += spaceLeft;
		}

		//calculate how much data still needs to be saved
		size -= spaceLeft;

		//allocate a new buffer, with enough space to hold the rest
		//of the data + extra
		expandBy(size + DEFAULT_ALLOC_SIZE);

		dstore = mChunks.back();
		dstore->append(data, size);
		
		mLogicalSize += size;
	}
} 

void cBuffer::capacity(const size_t &size)
{
	if(mBufferSize < size)
	{
		expandBy(size - mBufferSize);
	}
}

char *cBuffer::getBinary()
{
	mBinaryP = new char[mLogicalSize];
	char *retDataP = mBinaryP;
	for(std::vector<cDStore *>::iterator i = mChunks.begin(), q = mChunks.end(); i != q; ++i)
	{
		memcpy(retDataP, (*i)->mData, (*i)->mDataSize);
		retDataP += (*i)->mDataSize;
	}
	return mBinaryP;
}

void cBuffer::dumpBuffers()
{
	for(std::vector<cDStore *>::iterator i = mChunks.begin(), q = mChunks.end(); i != q; ++i)
	{
		std::cout << "BUFFER DATA: " << (*i)->getData() << std::endl;
		std::cout << "ALLOC SIZE: " << (*i)->mAllocSize << std::endl;
		std::cout << "BUFFER SIZE: " << (*i)->mDataSize << std::endl << std::endl;
	}
}

