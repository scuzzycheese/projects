/* 
 * File:   cQueue.h
 * Author: scuzzy
 *
 * Created on 12 December 2011, 10:30 AM
 */

#ifndef _CQUEUE_H
#define	_CQUEUE_H
#include <iostream>
#include <queue>
#include "cMessage.h"
#include <QWaitCondition>
#include <QMutex>

class cQueue
{
public:
	cQueue();
	virtual ~ cQueue();

	void enqueue(const cMessage &mess);
	void dequeue(cMessage &mess);


private:
	std::queue<cMessage> fifo;
	QWaitCondition messageInFifo;
	QMutex fifoEmpty;
	QMutex lockFifo;


};

#endif	/* _CQUEUE_H */

