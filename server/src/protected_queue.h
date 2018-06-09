#include <queue>
#include <mutex>

#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__

class ProtectedQueue{
	private:
		std::queue<char*> queue;
		std::mutex mutex;
	public:
		ProtectedQueue();
		
		~ProtectedQueue();
		
		void push(char* entry);
		
		void pop();
		
		char* front();
		
		bool isEmpty();
		
		void empty();
};

#endif
		
		
