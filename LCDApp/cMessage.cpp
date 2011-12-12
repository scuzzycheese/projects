/* 
 * File:   cMessage.cpp
 * Author: scuzzy
 * 
 * Created on 12 December 2011, 10:34 AM
 */

#include "cMessage.h"

cMessage::cMessage() : flag(0)
{
}

void cMessage::setFlag(int flag)
{
	this->flag = flag;
}

int cMessage::getFlag() const
{
	return flag;
}

cMessage::cMessage(const cMessage& orig)
{
}

cMessage::~cMessage()
{
}

