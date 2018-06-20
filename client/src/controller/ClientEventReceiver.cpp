#include "ClientEventReceiver.h"
#include "EventFactory.h"
#include "EventType.h"
#include <string>
#include <iostream>
#include <vector>

ClientEventReceiver::ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& q,
	Model& model, mainView& view, PreGameManager& preGame)
	: proxy(proxy), q(q), model(model), closed(false), view(view), preGame(preGame){	
}


ClientEventReceiver::~ClientEventReceiver() {
  while (!q.empty()) {
    delete q.pop();
  }
  //std::cout << "ClientEventReceiver destruido" << std::endl;
}



void ClientEventReceiver::run(){
	std::cout << "ClientEventReceiver destruido" << std::endl;
	try{
		while (!closed){
			char t = proxy.receiveChar();
			if (isPreGameEvent((int)t)){
				process(t);
				continue;
			}
			EventType type = static_cast<EventType>(t);
			Event* event = EventFactory::createEvent(type, proxy, model, view);
			q.push(event);
		}
	} catch (SocketError& e){
		this->stop();
	}

}



bool ClientEventReceiver::isPreGameEvent(int t){
	return  t >= 17 && t <= 21;
}

void ClientEventReceiver::process(int t){
	switch (t){
		case 17:
			std::cout << 17 <<std::endl;
			break;
		case 18:
			std::cout << 18 <<std::endl;
			break;
		case 19:
			std::cout << 19 <<std::endl;
			break;
		case 20:
			std::cout << 20 <<std::endl;
			break;
		case 21: //se agrega mapa al hall
			int size = proxy.receiveInt();
			for (int i = 0; i < size; i++){
				std::string name_map = proxy.receiveName();
				std::cout << name_map <<std::endl;
				preGame.addMap(name_map);
			}

			break;
	}
}

void ClientEventReceiver::stop(){
	closed = true;
	proxy.close();
}

bool ClientEventReceiver::isClosed() const{
	return closed;
}