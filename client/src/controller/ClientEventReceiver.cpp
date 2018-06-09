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

EventType getTypeEvent(int& type){
	switch (type){
		case 3: return W_MOVE;
		case 4: return START_TURN;
		case 5: return W_CHANGE_STATE;
		case 6: return B_POS;
		case 7: return B_EXPLOTE;
		case 8: return W_CUR_WEAPON;
		case 9: return W_CUR_AIM;
		case 10: return G_ENDGAME;
	}
	return W_MOVE;
}

void ClientEventReceiver::run(){
	std::cout << "ClientEventReceiver corriendo" << std::endl;
	try{
		while (!closed){
			int t = proxy.receiveInt();
			EventType type = getTypeEvent(t);
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