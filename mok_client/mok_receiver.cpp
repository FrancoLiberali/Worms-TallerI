#include "mok_receiver.h"

MokReceiver::MokReceiver(MokProxy& proxy_e) : proxy(proxy_e){
}

MokReceiver::~MokReceiver(){
}

void MokReceiver::stop(){
	{
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		this->keep_receiving = false;
	}
	// en mok proxy esta funcion no desbloquea, por lo que hay que tirar un enter o algo para que termine
	this->proxy.close_communication();
	
}

void MokReceiver::run(){
	bool keep = this->keep_receiving;
	while(keep){
		this->proxy.receive_event();
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		keep = this->keep_receiving;
	}
}
