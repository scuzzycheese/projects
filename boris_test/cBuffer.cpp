#include "cBuffer.h"


cBuffer::cBuffer() : dNumChunks(1)
{
	dChunks.push_back(cDStore(DEFAULT_ALLOC_SIZE));
}
