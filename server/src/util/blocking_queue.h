#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>
#include "util/queue.h"

class BlockingQueue : public Queue{
	private:
		std::condition_variable cv;

	public:
		// Crea una cola bloqueante de char*
		BlockingQueue();
		
		~BlockingQueue();
		
		// Devuelve si la cola esta vacia.
		virtual bool isEmpty(); 
		
		// Vacia la cola
		virtual void empty();
		
		// Encola un char* a la cola
		virtual void push(char* entry);
		
		// Descola un char* de la cola
		virtual char* pop();

	private:
		BlockingQueue(const BlockingQueue &) = delete;
		BlockingQueue &operator=(const BlockingQueue &) = delete;
};

#endif
