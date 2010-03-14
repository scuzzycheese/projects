#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "cDStore.h"
#include "cExceptions.h"

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

	private:
	/**
	 * Stop the compiler making me a copy constructor
	 * and an operator=
	 */
	cBuffer(const cBuffer& me);
	cBuffer &operator=(const cBuffer& me);

	public: 
	enum
	{
		DEFAULT_ALLOC_SIZE = 10
	};

	/**
	 * Creates a buffer with a default size
	 *
	 * @throw std::bad_alloc
	 */
	cBuffer();
	/**
	 * Creates a buffer with a given size
	 *
	 * @param size size of the initial block to allocate
	 * @throw std::bad_alloc
	 */
	cBuffer(const size_t &size);
	/**
	 * Creates a buffer with a given size and copy the contents of data into it
	 *
	 * @param data The data being copied into the buffer
	 * @param size The size of the buffer being copied in
	 */
	cBuffer(const char * const &data, const size_t &size);
	/**
	 * Create a buffer that that copies the data into it, of a given size or takes ownership
	 * 
	 * The data can either be copied in, or ownership of the pointer can be taken, if the last
	 * parameter is given as true. The buffer will have a capacity of whatever is specified
	 * afterwards. If the capacity specified is less than the size of the buffer being passed 
	 * in (taken ownership OR copied) this method will fail.
	 *
	 * @param data Data to be copied in or taken ownership of
	 * @param size Size of the data passed in
	 * @param capacity Overall capacity of the buffer (Must be greater or equal to size)
	 * @param takeOwnership Specify if you want to take ownership of the pointer
	 * @throw bad_alloc
	 * @throw bad_capacity
	 */
	cBuffer(char * const &data, const size_t &size, const size_t &capacity, bool takeOwnership);

	/**
	 * Create a buffer that that copies the data into it and sanction a size
	 *
	 * @param data Data to be copied into the buffer
	 * @param size Size of the data to be copied
	 * @param capacity Overall capacity of the buffer (Must be greater or equal to size)
	 * @throw bad_alloc
	 * @throw bad_capacity
	 */
	cBuffer(const char * const &data, const size_t &size, const size_t &capacity);

	~cBuffer();

	/**
	 * Copy data into the beginning of the buffer
	 *
	 * @param data Data to be copied into the buffer
	 * @param size Size of the data to be copied in
	 * @throw std::bad_alloc
	 */
	void copy(const char *data, size_t size);

	/**
	 * Append data onto the end of the buffer
	 *
	 * @param data Data to be appended to the buffer
	 * @param size Size of the data to be appended
	 * @throw std::bad_alloc
	 */
	void append(const char *data, size_t size);

	/**
	 * Make sure the buffer has a specific capacity(without re-allocation)
	 * 
	 * @param size Size of the buffers capacity
	 * @throw std::bad_alloc
	 */
	void capacity(const size_t &size);


	/**
	 * Returns a char * pointer to a copy of the buffer.
	 *
	 * The pointer is only gauranteed until another modifying action takes place
	 * on the buffer. Otherwise the behavior is undefined.
	 * NOTE: modifying the contents of the returned pointer does not affect
	 * the content ofthe buffer
	 *
	 * @return pointer to a copy of the buffer as a contiguous block
	 */
	char *getBinary();

	/**
	 * Returns the logical size of the buffer
	 *
	 */
	size_t getSize();
	
	void dumpBuffers();
};


#endif

