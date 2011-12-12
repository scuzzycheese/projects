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
	enum messageType
	{
		MESSAGE_NONE,
		MESSAGE_FLUSH
	};

	cMessage();
	cMessage(messageType mt);
	virtual ~ cMessage();
	void setMessageType(messageType mt);
	int getMessageType() const;



private:
	messageType messageTypeVal;

};

#endif	/* _CMESSAGE_H */

