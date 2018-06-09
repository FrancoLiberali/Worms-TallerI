#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

class Event;
#include <queue>
#include <string>
#include "Event.h"
#include "../view/mainView.h"

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