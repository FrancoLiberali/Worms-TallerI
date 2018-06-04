#include "protected_queue.h"

ProtectedQueue::ProtectedQueue(){
}

ProtectedQueue::~ProtectedQueue(){
}

void ProtectedQueue::push(char* entry){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->queue.push(entry);
}

void ProtectedQueue::pop(){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->queue.pop();
}

char* ProtectedQueue::front(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->queue.front();
}

bool ProtectedQueue::isEmpty(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->queue.empty();
}
