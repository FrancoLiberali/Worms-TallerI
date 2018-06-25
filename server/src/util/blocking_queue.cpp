#include "util/blocking_queue.h"

BlockingQueue::BlockingQueue(){
}

BlockingQueue::~BlockingQueue(){
	this->empty();
}

bool BlockingQueue::isEmpty(){
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->queue.empty();
}

void BlockingQueue::empty(){
	std::unique_lock<std::mutex> lock(this->mutex);
	while(!this->queue.empty()){
		char* val = this->queue.front();
		this->queue.pop();
		delete[] val;
	}
}

void BlockingQueue::push(char* entry){
	std::unique_lock<std::mutex> lock(this->mutex);
	if (this->queue.empty()){
		cv.notify_all();
	}
	this->queue.push(entry);
}

char* BlockingQueue::pop(){
	std::unique_lock<std::mutex> lock(this->mutex);
	while (this->queue.empty()){
		cv.wait(lock);
	}
	char* val = this->queue.front();
	this->queue.pop();
	
	return val;
}
	


