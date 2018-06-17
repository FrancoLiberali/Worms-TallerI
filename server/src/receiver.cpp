#include "receiver.h"
#include "socket_error.h"
#include <iostream>

Receiver::Receiver(Socket& socket, Queue* queue){
	Socket active = socket.accept();
	this->proxy = new Proxy(std::move(active), queue);
}

Receiver::~Receiver(){
	delete this->proxy;
}

Proxy* Receiver::getProxy(){
	return this->proxy;
}

void Receiver::stop(){
	{
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		this->keep_receiving = false;
	}
	this->proxy->close_communication();
	
}

void Receiver::run(){
	bool keep = this->keep_receiving;
	while(keep){
		try{
			this->proxy->receive_event();
			std::lock_guard<std::mutex> lock(this->keep_mutex);
			keep = this->keep_receiving;
		} catch (SocketError& e){
			this->stop();
			std::lock_guard<std::mutex> lock(this->keep_mutex);
			keep = this->keep_receiving;
		}
	}
}
