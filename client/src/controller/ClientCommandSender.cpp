#include "ClientCommandSender.h"

#include <iostream>

ClientCommandSender::ClientCommandSender(ProxyClient& proxy, Queue<ClientCommand*>& queue)
	:proxy(proxy), queue(queue), closed(false){}

ClientCommandSender::~ClientCommandSender(){
	while(!queue.empty()){
		delete (queue.pop());
	}	
}

void ClientCommandSender::run(){
	while (!closed){
		ClientCommand* cmd = queue.pop();
		if (cmd != nullptr){
			try {
				cmd->send(proxy);
				delete cmd;
			} catch (SocketError& e){
				std::cout << e.what() << std::endl;
				this->stop();
			}
		}
		else{
			this->stop();
		}
	}
}

void ClientCommandSender::stop(){
	if (closed)
		return;
	closed = true;
	proxy.close();
}

bool ClientCommandSender::isClosed() const{
	return closed;
}