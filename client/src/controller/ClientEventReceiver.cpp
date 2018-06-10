#include "ClientEventReceiver.h"
#include "EventFactory.h"
#include "EventType.h"
#include <fstream>
#include <iostream>
#include <sstream>

ClientEventReceiver::ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& q,
	Model& model, mainView& view): proxy(proxy), q(q), model(model), 
									closed(false), view(view){
	
	std::cout << "ClientEventReceiver construido" << std::endl;
}


ClientEventReceiver::~ClientEventReceiver() {
  while (!q.empty()) {
    delete q.pop();
  }
  std::cout << "ClientEventReceiver destruido" << std::endl;
}



EventType getTypeEvent(char& type){
	//return static_cast<EventType>(type);
}

void ClientEventReceiver::run(){
	std::cout << "ClientEventReceiver corriendo" << std::endl;
	try{
		while (!closed){
			std::cout<<"se llama al socket"<<std::endl;
			char t = proxy.receiveChar();
			EventType type = static_cast<EventType>(t);
			std::cout<<"se recibe un mensaje del socket"<<std::endl;
			Event* event = EventFactory::createEvent(type, proxy, model, view);
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