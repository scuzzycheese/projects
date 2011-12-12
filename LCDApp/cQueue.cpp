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

	std::cout << "Adding Message to the Queue: " << mess.getFlag() << std::endl;
	fifo.push(mess);
	messageInFifo.wakeAll();

	lockFifo.unlock();
}

void cQueue::dequeue(cMessage &mess)
{
	fifoEmpty.lock();
	while(fifo.empty())
	{
		std::cout << "Queue Empty, waiting..." << std::endl;
		messageInFifo.wait(&fifoEmpty);
	}
	mess = fifo.front();
	std::cout << "Queue size: " << fifo.size() << std::endl;
	std::cout << "Pulling Message off the queue: " << mess.getFlag() << std::endl;
	fifo.pop();

	fifoEmpty.unlock();
}


cQueue::~cQueue()
{
}

