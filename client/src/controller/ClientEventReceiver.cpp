#include "ClientEventReceiver.h"
#include "EventFactory.h"
#include "EventType.h"
#include <fstream>
#include <iostream>
#include <sstream>

ClientEventReceiver::ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& q,
	Model& model, mainView& view): proxy(proxy), q(q), model(model), 
									closed(false), view(view){	
}


ClientEventReceiver::~ClientEventReceiver() {
  while (!q.empty()) {
    delete q.pop();
  }
  std::cout << "ClientEventReceiver destruido" << std::endl;
}



void ClientEventReceiver::run(){
	try{
		while (!closed){
			char t = proxy.receiveChar();
			EventType type = static_cast<EventType>(t);
			Event* event = EventFactory::createEvent(type, proxy, model, view);
			q.push(event);
		}
	} catch (SocketError& e){
		this->stop();
	}

}

void ClientEventReceiver::stop(){
	closed = true;
	proxy.close();
}

bool ClientEventReceiver::isClosed() const{
	return closed;
}