/* 
 * File:   cMessage.h
 * Author: scuzzy
 *
 * Created on 12 December 2011, 10:34 AM
 */

#ifndef _CMESSAGE_H
#define	_CMESSAGE_H

class cMessage
{
public:
	cMessage();
	virtual ~ cMessage();
	void setFlag(int flag);
	int getFlag() const;
private:
	int flag;

};

#endif	/* _CMESSAGE_H */

