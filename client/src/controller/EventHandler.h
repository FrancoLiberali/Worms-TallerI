#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

class Event;
#include <queue>
#include <string>
#include "event/Event.h"
#include "../view/mainView.h"
#include "../model/Model.h"

class Model;
/**
* @class EventHandler
* Manejador principal de eventos, usa una cola para almacenar
* los eventos del server como del cliente que alteran a la vista
*/
class EventHandler {
private:
	mainView* view;
	Model* model;
	std::queue<Event*> eventQueue;
public:
	void add(Event* event);
	void setView(mainView* view);
	void setModel(Model* model);
  	bool empty();
  	Event* get();
};

#endif