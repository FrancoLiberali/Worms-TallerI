#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

class Event;
#include <queue>
#include <string>
#include "event/Event.h"
#include "../view/mainView.h"

/**
* @class EventHandler
* Manejador principal de eventos, usa una cola para almacenar
* los eventos del server como del cliente que alteran a la vista
*/
class EventHandler {
private:
	mainView* view;
	std::queue<Event*> eventQueue;
public:
	void add(Event* event);
	void setView(mainView *view);
  	bool empty();
  	Event* get();
};

#endif