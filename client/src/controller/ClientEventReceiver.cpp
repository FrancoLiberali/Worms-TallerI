#include "ClientEventReceiver.h"
#include "EventFactory.h"
#include "EventType.h"
#include <fstream>
#include <iostream>
#include <sstream>

ClientEventReceiver::ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& q,
	std::string socket):socket_file(socket), proxy(proxy), q(q), closed(false){
	
	std::cout << "ClientEventReceiver construido" << std::endl;
}


ClientEventReceiver::~ClientEventReceiver() {
  while (!q.empty()) {
    delete q.pop();
  }
  //proxy.close();
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

EventType getTypeEvent(int& type){
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
	/*try{
		while (!closed){
			int t = proxy.receiveInt();
			EventType type = getTypeEvent(t);
			Event* event = EventFactory::createEvent(type, proxy);
			std::cout << i <<std::endl;
			q.push(event);
		}
	} catch (const SocketException& e){
		this->stop();
	}*/

}

void ClientEventReceiver::stop(){
	closed = true;
	//cerramos el socket
}

bool ClientEventReceiver::isClosed() const{
	return closed;
}