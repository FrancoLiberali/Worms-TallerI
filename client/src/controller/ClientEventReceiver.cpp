#include "ClientEventReceiver.h"
#include <fstream>
#include <iostream>

ClientEventReceiver::ClientEventReceiver(std::string socket,Queue& q)
					: socket_file(socket), q(q), closed(false){

	std::cout << "ClientEventReceiver construido" << std::endl;
}

ClientEventReceiver::~ClientEventReceiver() {
  while (!q.empty()) {
    q.pop();
  }
  std::cout << "ClientEventReceiver destruido" << std::endl;
}

void ClientEventReceiver::run(){
	std::cout << "ClientEventReceiver corriendo" << std::endl;
  	std::ifstream ifs(socket_file);
	if (!ifs.is_open()){
		  std::cout << "no se abrio el archivo" << std::endl;
		  return;
	}

	std::string event;
	while(!closed){
		//leemos del "socket"
		std::getline(ifs, event);
		//std::cout << event << std::endl;
		q.push(event);
		if (ifs.eof())
			this->stop();
	}
}

void ClientEventReceiver::stop(){
	closed = true;
}

bool ClientEventReceiver::isClosed() const{
	return closed;
}