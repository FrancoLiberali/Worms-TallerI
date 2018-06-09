#include "EventHandler.h"

void EventHandler::setView(mainView* view){
	this->view = view;
}

void EventHandler::add(Event* event){
	event->setView(view);
	eventQueue.push(event);
}

bool EventHandler::empty(){
	return eventQueue.empty();
}

Event* EventHandler::get(){
	Event* aux = eventQueue.front();
	eventQueue.pop();
	return aux;
}
