#include "ClientEventReceiver.h"
#include "EventFactory.h"
#include "EventType.h"
#include <fstream>
#include <iostream>
#include <sstream>

ClientEventReceiver::ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& q,
	Model& model): proxy(proxy), q(q), model(model), closed(false){
	
	std::cout << "ClientEventReceiver construido" << std::endl;
}


ClientEventReceiver::~ClientEventReceiver() {
  while (!q.empty()) {
    delete q.pop();
  }
  std::cout << "ClientEventReceiver destruido" << std::endl;
}

EventType getTypeEvent(char& type){
	switch (type){
		case 5: return START_TURN;
		case 6: return W_MOVE;
		case 7: return W_CHANGE_STATE;
		case 8: return B_POS;
		case 9: return B_EXPLOTE;
		case 10: return W_CUR_WEAPON;
		case 11: return W_CUR_AIM;
		case 12: return W_CHANGE_LIFE;
		case 13: return G_PLAYER_OFF;
		case 14: return G_PLAYER_WIN;
	}
	return W_MOVE;
}

void ClientEventReceiver::run(){
	std::cout << "ClientEventReceiver corriendo" << std::endl;
	try{
		while (!closed){
			std::cout<<"se llama al socket"<<std::endl;
			char t = proxy.receiveChar();
			EventType type = getTypeEvent(t);
			std::cout<<"se recibe un mensaje del socket"<<std::endl;
			Event* event = EventFactory::createEvent(type, proxy, model);
			q.push(event);
		}
	} catch (SocketError& e){
		this->stop();
	}

}

void ClientEventReceiver::stop(){
	closed = true;
}

bool ClientEventReceiver::isClosed() const{
	return closed;
}