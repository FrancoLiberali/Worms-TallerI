#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

/*Template Cola protegida*/
#include <queue>
#include <mutex>
#include <condition_variable>
#include "queue.h"

class BlockingQueue : public Queue{
	private:
		std::condition_variable cv;

	public:
		BlockingQueue();
		
		~BlockingQueue();
  
		virtual bool isEmpty(); 
  
		virtual void empty();
  
		virtual void push(const char* entry);

		virtual char* pop();

	private:
		BlockingQueue(const BlockingQueue &) = delete;
		BlockingQueue &operator=(const BlockingQueue &) = delete;
};

#endif
