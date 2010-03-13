#include "cBuffer.h"


cBuffer::cBuffer() : mNumChunks(1), mBufferSize(DEFAULT_ALLOC_SIZE), mLogicalSize(0)
{
	/**
	 * NOTE: catch an exception here (allocation
	 * failure)
	 */
	mChunks.push_back(new cDStore(DEFAULT_ALLOC_SIZE));
}

cBuffer::cBuffer(const size_t &size) : mNumChunks(1), mBufferSize(size), mLogicalSize(0)
{
	mChunks.push_back(new cDStore(size));
}

cBuffer::cBuffer(const size_t &size, const size_t &growToWithoutRealloc) : mNumChunks(1), mBufferSize(growToWithoutRealloc), mLogicalSize(0)
{
	mChunks.push_back(new cDStore(growToWithoutRealloc));
}

cBuffer::cBuffer(char * const &data, const size_t &size) : mNumChunks(1), mBufferSize(size), mLogicalSize(size)
{
	mChunks.push_back(new cDStore(size, data));
}

cBuffer::cBuffer(char * const &data, const size_t &size, const size_t &growToWithoutRealloc, bool takeOwnership) : mBufferSize(growToWithoutRealloc), mLogicalSize(size)
{
	if(takeOwnership)
	{
		mChunks.push_back(new cDStore(size, data, takeOwnership));
		mChunks.push_back(new cDStore(size));
		mNumChunks = 2;
	}
	else
	{
		mChunks.push_back(new cDStore(growToWithoutRealloc, data));
		mNumChunks = 1;
	}
}




cBuffer::~cBuffer()
{
}



void cBuffer::copy(char *data, size_t size)
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
		}

		//calculate how much data still needs to be saved
		size -= spaceLeft;

		//allocate a new buffer, with enough space to hold the rest
		//of the data + extra
		mChunks.push_back(new cDStore(size + DEFAULT_ALLOC_SIZE));

		dstore = mChunks.back();
		dstore->append(data, size);
		
		mNumChunks ++;
		mBufferSize += size + DEFAULT_ALLOC_SIZE;
		mLogicalSize += size;
	}
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

char *cBuffer::currentBuffer()
{
	return mChunks.back()->getData();
}

