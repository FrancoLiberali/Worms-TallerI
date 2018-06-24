#include "EventHandler.h"

void EventHandler::setView(mainView* view){
	this->view = view;
}

void EventHandler::setModel(Model* model){
	this->model = model;
}


void EventHandler::add(Event* event){
	event->setView(view);
	event->setModel(model);
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
