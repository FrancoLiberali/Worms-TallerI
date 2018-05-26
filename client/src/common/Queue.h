#ifndef _QUEUE_H
#define _QUEUE_H

/*Cola protegida para strings*/
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class Queue {
private:
	std::queue<std::string> q;
	std::mutex m;
	std::condition_variable cv;
	Queue(const Queue &) = delete;
  	Queue &operator=(const Queue &) = delete;
public:
	Queue();
	~Queue();
	bool empty();
	void push(std::string msg);
	std::string pop();	
};

#endif