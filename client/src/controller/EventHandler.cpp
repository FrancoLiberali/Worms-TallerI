#include "EventHandler.h"

/*void EventHandler::setView(View* view){
	this->view = view;
}*/

void EventHandler::add(std::string event){
	eventQueue.push(event);
}

bool EventHandler::empty(){
	return eventQueue.empty();
}

std::string EventHandler::get(){
	std::string aux = eventQueue.front();
	eventQueue.pop();
	return aux;
}
