#include "protected_queue.h"

ProtectedQueue::ProtectedQueue(){
}

ProtectedQueue::~ProtectedQueue(){
	this->empty();
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

void ProtectedQueue::push(char* entry){
	std::lock_guard<std::mutex> lock(this->mutex);
	this->queue.push(entry);
}

char* ProtectedQueue::pop(){
	std::lock_guard<std::mutex> lock(this->mutex);
	char* val = this->queue.front();
	this->queue.pop();
	
	return val;
}


		
