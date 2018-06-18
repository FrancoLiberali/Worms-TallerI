#include "mok_receiver.h"
#include "socket_error.h"

MokReceiver::MokReceiver(MokProxy& proxy_e) : proxy(proxy_e){
}

MokReceiver::~MokReceiver(){
}

void MokReceiver::stop(){
	{
		std::lock_guard<std::mutex> lock(this->keep_mutex);
		this->keep_receiving = false;
	}
	this->proxy.close_communication();
	
}

void MokReceiver::run(){
	bool keep = this->keep_receiving;
	while(keep){
		try{
			this->proxy.receive_event();
			std::lock_guard<std::mutex> lock(this->keep_mutex);
			keep = this->keep_receiving;
		} catch (SocketError& e){
			//this->stop();
			//std::lock_guard<std::mutex> lock(this->keep_mutex);
			//keep = this->keep_receiving;
			keep = false;
		}
			
	}
}
