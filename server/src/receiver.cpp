#include "receiver.h"

//Receiver::Receiver(Proxy& proxy_e, ProtectedQueue& queue_e) : proxy(proxy_e), queue(queue_e){
Receiver::Receiver(MokProxy& proxy_e, ProtectedQueue& queue_e) : proxy(proxy_e), queue(queue_e){
}

Receiver::~Receiver(){
}

void Receiver::stop(){
	{
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		this->keep_receiving = false;
	}
	// en mok proxy esta funcion no desbloquea, por lo que hay que tirar un enter o algo para que termine
	this->proxy.close_communication();
	
}

void Receiver::run(){
	bool keep = this->keep_receiving;
	while(keep){
		this->proxy.receive_event(queue);
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		keep = this->keep_receiving;
	}
}
