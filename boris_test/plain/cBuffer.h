#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "cDStore.h"

#define DEFAULT_ALLOC_SIZE 10

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


	/**
	 * Returns a char * pointer to a copy of the buffer.
	 *
	 * The pointer is only gauranteed until another modifying action takes place
	 * on the buffer. Otherwise the behavior is undefined.
	 *
	 * @return pointer to a copy of the buffer as a contiguous block
	 */
	char *getBinary();
	
	void dumpBuffers();
};


#endif

