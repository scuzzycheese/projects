#ifndef CDSTORE_H
#define CDSTORE_H

#include <vector>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <assert.h>

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
	cDStore(const size_t &size) throw(std::bad_alloc);

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
	cDStore(const size_t &size, char * const &data, bool takeOwnership = false) throw(std::bad_alloc);

	~cDStore();

	size_t mSpaceLeft();

	/**
	 * Copy data into the beginning of the block
	 *
	 * @param[in] data Data to be copied
	 * @param[in] size Size of the data to be copied
	 */
	void copy(char * const &data, const size_t &size);

	void append(char * const &data, const size_t &size);

};

#endif
