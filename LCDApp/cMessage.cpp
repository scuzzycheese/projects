/* 
 * File:   cMessage.cpp
 * Author: scuzzy
 * 
 * Created on 12 December 2011, 10:34 AM
 */

#include "cMessage.h"

cMessage::cMessage() : messageTypeVal(MESSAGE_NONE)
{
}

void cMessage::setMessageType(messageType mt)
{
	this->messageTypeVal = mt;
}

int cMessage::getMessageType() const
{
	return messageTypeVal;
}

cMessage::cMessage(messageType mt) : messageTypeVal(mt)
{
}

cMessage::~cMessage()
{
}

