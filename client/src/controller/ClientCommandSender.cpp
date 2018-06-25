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
			cmd->send(proxy);
			delete cmd;
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