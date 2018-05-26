#include "Queue.h"

Queue::Queue(){}

Queue::~Queue(){}

bool Queue::empty(){
	std::unique_lock<std::mutex> lck(m);
	return q.empty();
}

void Queue::push(std::string msg){
	std::unique_lock<std::mutex> lck(m);
	if (q.empty()){
		cv.notify_all();
	}
	q.push(msg);
}

std::string Queue::pop(){
	std::unique_lock<std::mutex> lck(m);
	while (q.empty()){
		cv.wait(lck);
	}

	std::string msg = q.front();
	q.pop();

	return msg;
}