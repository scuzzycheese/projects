#include "cBuffer.h"


cBuffer::cBuffer() : dNumChunks(1)
{
	/**
	 * NOTE: catch an exception here (allocation
	 * failure
	 */
	dChunks.push_back(cDStore(DEFAULT_ALLOC_SIZE));
}
