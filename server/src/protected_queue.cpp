#include "protected_queue.h"

ProtectedQueue::ProtectedQueue(){
}

ProtectedQueue::~ProtectedQueue(){
	this->empty();
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

void ProtectedQueue::empty(){
	std::lock_guard<std::mutex> lock(this->mutex);
	while (!this->queue.empty()){
		char* msj = this->queue.front();
		delete[] msj;
		this->queue.pop();
	}
}
		
