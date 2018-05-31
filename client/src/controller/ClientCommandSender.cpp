#include "ClientCommandSender.h"

#include <iostream>

ClientCommandSender::ClientCommandSender(std::string socket, Queue<ClientCommand*>& queue)
	:socket_file(socket), queue(queue), closed(false){}

ClientCommandSender::~ClientCommandSender(){
	while(!queue.empty()){
		delete (queue.pop());
	}
}

void ClientCommandSender::run(){
	//Acá se enviaria los comandos al server
	std::cout << "Sender running" << std::endl;
}

void ClientCommandSender::stop(){
	closed = true;
}

bool ClientCommandSender::isClosed() const{
	return closed;
}