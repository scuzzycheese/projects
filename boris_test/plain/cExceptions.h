#ifndef CEXCEPTIONS_H
#define CEXCEPTIONS_H


#include <exception>
#include <string>

class bad_capacity : public std::exception
{
	std::string mMessage;

	public:
	bad_capacity(const std::string& msg = "Capacity Exception") : mMessage(msg) {}
	~bad_capacity() throw() {}

	virtual const char* what() const throw()
	{
		return mMessage.c_str();
	}
};
	
#endif

