/* 
 * File:   cQueue.cpp
 * Author: scuzzy
 * 
 * Created on 12 December 2011, 10:30 AM
 */

#include "cQueue.h"

cQueue::cQueue() : fifo()
{
}


void cQueue::enqueue(const cMessage &mess)
{
	lockFifo.lock();

	fifo.push(mess);
	messageInFifo.wakeAll();

	lockFifo.unlock();
}

void cQueue::dequeue(cMessage &mess)
{
	fifoEmpty.lock();
	while(fifo.empty())
	{
		messageInFifo.wait(&fifoEmpty);
	}
	mess = fifo.front();
	fifo.pop();

	fifoEmpty.unlock();
}


cQueue::~cQueue()
{
}

