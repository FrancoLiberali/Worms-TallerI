#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <queue>
#include <mutex>

class Queue{
	protected:
		std::queue<char*> queue;
		std::mutex mutex;
	public:
		// Crea una cola de char*
		Queue() {}
		
		Queue(Queue&& other) : queue(std::move(other.queue)){}
		
		~Queue() {}
		
		// Devuelve si la cola esta vacia.
		virtual bool isEmpty() = 0;
		
		// Vacia la cola
		virtual void empty() = 0;
		
		// Encola un char* a la cola
		virtual void push(char* entry) = 0;
		
		// Descola un char* de la cola
		virtual char* pop() = 0;
};

#endif
