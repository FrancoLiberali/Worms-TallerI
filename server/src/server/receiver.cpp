#include "server/receiver.h"
#include "server/socket_error.h"
#include <iostream>

Receiver::Receiver(Socket active, Queue* queue) : proxy(std::move(active), queue){
}

Receiver::~Receiver(){
}

Proxy& Receiver::getProxy(){
	return this->proxy;
}

void Receiver::stop(){
	{
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		this->keep_receiving = false;
	}
	this->proxy.closeCommunication();
	
}

void Receiver::run(){
	bool keep = this->keep_receiving;
	while(keep){
		try{
			this->proxy.receiveEvent();
			std::lock_guard<std::mutex> lock(this->keep_mutex);
			keep = this->keep_receiving;
		} catch (SocketError& e){
			this->stop();
			std::lock_guard<std::mutex> lock(this->keep_mutex);
			keep = this->keep_receiving;
		}
	}
}

Receiver::Receiver(Receiver&& other) : proxy(std::move(other.proxy)), 
	keep_receiving(other.keep_receiving){
}
