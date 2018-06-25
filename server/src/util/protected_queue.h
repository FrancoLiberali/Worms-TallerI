#include <queue>
#include <mutex>
#include "util/queue.h"

#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__

class ProtectedQueue: public Queue{
	public:
		//Crea una cola protegida de char*
		ProtectedQueue();
		
		ProtectedQueue(ProtectedQueue&& other);
		
		~ProtectedQueue();
		
		//Devuelve true si la cola esta vacia.
		virtual bool isEmpty(); 
		
		// Vacia la cola
		virtual void empty();
		
		//Agrega un char* a la cola
		virtual void push(char* entry);
		
		//Saca un char* de la cola.
		virtual char* pop();
};

#endif
		
		
