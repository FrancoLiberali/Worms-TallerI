#include "ClientCommandSender.h"

#include <iostream>

ClientCommandSender::ClientCommandSender(ProxyClient& proxy, Queue<ClientCommand*>& queue)
	:proxy(proxy), queue(queue), closed(false){}

ClientCommandSender::~ClientCommandSender(){
	while(!queue.empty()){
		delete (queue.pop());
	}
	//std::cout << "Sender cerrado" << std::endl;

}

void ClientCommandSender::run(){
	//Acá se enviaria los comandos al server
	//std::cout << "Sender running" << std::endl;
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
	closed = true;
}

bool ClientCommandSender::isClosed() const{
	return closed;
}