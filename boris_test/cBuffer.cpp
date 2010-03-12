#include "cBuffer.h"


void cBuffer::allocateInternalBuffer(size_t size)
{
	/**
	 * NOTE: catch an exception here (allocation
	 * failure)
	 */
	mChunks.push_back(new cDStore(size));
	mNumChunks = 1;
}



cBuffer::~cBuffer()
{
}



void cBuffer::copy(char *data,  size_t size)
{
	cDStore *dstore = mChunks.back();
	size_t spaceLeft = dstore->mSpaceLeft();

	if(spaceLeft >= size)
	{
		dstore->append(data, size);
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
	}
} 

char *cBuffer::currentBuffer()
{
	return mChunks.back()->getData();
}

