#include "cBuffer.h"


cBuffer::cBuffer() : dNumChunks(1)
{
	/**
	 * NOTE: catch an exception here (allocation
	 * failure)
	 */
	dChunks.push_back(new cDStore(DEFAULT_ALLOC_SIZE));
}



cBuffer::~cBuffer()
{
}



void cBuffer::copy(char *data,  size_t size)
{
	cDStore *dstore = dChunks.back();
	size_t spaceLeft = dstore->mSpaceLeft();

	if(spaceLeft >= size)
	{
		dstore->mAppend(data, size);
	}
	else
	{
		if(spaceLeft > 0)
		{
			dstore->mAppend(data, spaceLeft);
			data += spaceLeft;
		}

		//calculate how much data still needs to be saved
		size -= spaceLeft;

		//allocate a new buffer, with enough space to hold the rest
		//of the data + extra
		dChunks.push_back(new cDStore(size + DEFAULT_ALLOC_SIZE));

		dstore = dChunks.back();
		dstore->mAppend(data, size);
	}
} 

char *cBuffer::mCurrentBuffer()
{
	return dChunks.back()->mGetData();
}

