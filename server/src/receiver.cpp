#include "receiver.h"
#include "socket_error.h"

Receiver::Receiver(Socket& socket, ProtectedQueue& queue_e) : queue(queue_e){
	Socket active = socket.accept_();
	this->proxy = new Proxy(std::move(active));
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
			this->proxy->receive_event(queue);
			std::lock_guard<std::mutex> lock(this->keep_mutex);
			keep = this->keep_receiving;
		} catch (SocketError& e){
			this->stop();
			std::lock_guard<std::mutex> lock(this->keep_mutex);
			keep = this->keep_receiving;
		}
	}
}
