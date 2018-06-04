#include "ClientEventReceiver.h"
#include "EventFactory.h"
#include "EventType.h"
#include <fstream>
#include <iostream>
#include <sstream>


ClientEventReceiver::ClientEventReceiver(std::string socket,Queue<Event*>& q)
					: socket_file(socket), q(q), closed(false){

	std::cout << "ClientEventReceiver construido" << std::endl;
}

ClientEventReceiver::~ClientEventReceiver() {
  while (!q.empty()) {
    q.pop();
  }
  std::cout << "ClientEventReceiver destruido" << std::endl;
}

/*Funcion auxiliar para ver el tipo del evento*/
EventType getTypeEvent(std::stringstream& ss){
	int type = 0;
	ss >> type;

	switch (type){
		case 0: return W_CHANGE_STATE;
		case 1: return W_MOVE;
		case 2: return W_JUMP;
		case 3: return W_ATTACK;
		case 4: return W_DEATH;
		case 5: return G_ENDGAME;
	}
	return W_MOVE;
}

void ClientEventReceiver::run(){
	std::cout << "ClientEventReceiver corriendo" << std::endl;
  	std::ifstream ifs(socket_file);
	if (!ifs.is_open()){
		  std::cout << "no se abrio el archivo" << std::endl;
		  return;
	}

	std::string str;
	while(!closed){
		//leemos del "socket"
		std::getline(ifs, str);
		std::cout << str << std::endl;
		std::stringstream ss(str);
		EventType type = getTypeEvent(ss);
		Event* event = EventFactory::createEvent(type, ss);
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