#ifndef CBUFFERBASE_H
#define CBUFFERBASE_H

#include <stdint.h>
#include <string.h>

#define DEFAULT_ALLOC_SIZE 10





/*
template < typename Derived >
class cBaseClass
{
public:
cBaseClass (  )
{
Derived * d = (Derived *) this;
d->DoSomething ( );
}
}

class type1 : public cBaseClass < type1 >
{
type1 ( )
{
}
};
*/



template <typename Derived>
class cBufferBase
{

	size_t mBufferSize;
	size_t mLogicalSize;

	public:

	cBufferBase()
	{
		setLogicalSize(DEFAULT_ALLOC_SIZE);
		setBufferSize(DEFAULT_ALLOC_SIZE);
	
		Derived *d = (Derived *)this;
		d->allocateInternalBuffer(DEFAULT_ALLOC_SIZE);
	}
	
	cBufferBase(size_t size)
	{
		setLogicalSize(size);
		setBufferSize(size);
	
		Derived *d = (Derived *)this;
		d->allocateInternalBuffer(size);
	}
	
	cBufferBase(size_t size, size_t growToWithoutRealloc)
	{
		setLogicalSize(size);
		setBufferSize(growToWithoutRealloc);
	
		Derived *d = (Derived *)this;
		d->allocateInternalBuffer(growToWithoutRealloc);
	}
	
	cBufferBase(char *data, size_t size)
	{
		setLogicalSize(size);
		setBufferSize(size);
	
		Derived *d = (Derived *)this;
		d->allocateInternalBuffer(size);
	
		d->copyToInternalBuffer(data, size);
	}
	
	cBufferBase(char *data, size_t size, size_t growToWithoutRealloc)
	{
		setLogicalSize(size);
		setBufferSize(growToWithoutRealloc);
	
		Derived *d = (Derived *)this;
		d->allocateInternalBuffer(growToWithoutRealloc);
	
		d->copyToInternalBuffer(data, size);
	}
	
	cBufferBase(char *data, size_t size, size_t growToWithoutRealloc, bool takeOwnership)
	{
		setLogicalSize(size);
		setBufferSize(growToWithoutRealloc);
		
		
	}
	
	void setLogicalSize(size_t size)
	{
		mLogicalSize = size;
	}
	
	void setBufferSize(size_t size)
	{
		mBufferSize = size;
	}

	/*
	void copy(char *data, size_t size)
	{
		((Derived *)this)->copy(data, size);
	}

	char *currentBuffer()
	{
		return ((Derived *)this)->currentBuffer();
	}
	*/
	
};











/*	
	cBufferBase();
	cBufferBase(size_t size);
	cBufferBase(size_t size, size_t growToWithoutRealloc);
	cBufferBase(char *data, size_t size);
	cBufferBase(char *data, size_t size, size_t growToWithoutRealloc);
	cBufferBase(char *data, size_t size, size_t growToWithoutRealloc, bool takeOwnership);
	
	void copy(char *buff, size_t size);

	void append(char *buff, size_t size);

	void capacity(size_t size);
*/

	/**
	 * NOTE: This will be implemented in the contiguous
	 * memory scheme class
	 */
	//char *data();


/*
	virtual void allocateInternalBuffer(size_t size) = 0;
	virtual void setLogicalSize(size_t size);
	virtual void setBufferSize(size_t size);
	virtual void copyToInternalBuffer(char *data, size_t size) = 0;
	virtual void appendToInternalBuffer(char *data, size_t size) = 0;
	virtual void setTakeOwnershipFlag(bool flag);
	virtual void setInternalCapacity(size_t size) = 0;
*/


/*
  const char* buf = ...
  size_t n = ...
  size_t c = ...

  buffer b; // Allocate an empty buffer.

  b.copy (buf, n); // Copy data into the buffer, growing the underlying
                   // buffer if necessary. After this call b.size () == n.

  buffer b1 (n); // Allocate a buffer 'n' bytes long.
  memcpy (b1.data (), buf, n);

  buffer b2 (0, 1024); // Allocate a buffer 0 bytes long with capacity
                       // to grow without reallocation to 1024 bytes.
  b2.size (n); 
  memcpy (b2.data (), buf, n);

  
  buffer b3 (1024, 5 * 1024); // Allocate a buffer 1024 bytes long with 
                              // capacity to grow without reallocation to 
                              // 5*1024 bytes.
  memset (b3.data (), 0, 1024);

  for (int i = 0; i < 5; ++i)
    b3.append (buf, n); // Append the data to the buffer.

  if (b3.capacity () < 10 * 1024)
    b3.capacity (10 * 1024); // Make sure the buffer has this capacity.

  buffer b4 (buf, n); // Allocate a buffer 'n' bytes long and copy the
                      // data.

  buffer b5 (buf, n, 5 * 1024); // Allocate a buffer 'n' bytes long and 
                                // with capacity to grow without 
                                // reallocation to 5*1024 bytes. Copy
                                // the date over.

  buffer b6 (buf, n, n, true);  // Assume ownership of the buffer with
                                // size 'n' (second argument) and capacity 
                                // 'n' (third argument).

*/

#endif

