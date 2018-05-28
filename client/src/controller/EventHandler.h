#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

class Event;
#include <queue>
#include <string>
#include "Event.h"
#include "../view/View.h"

class EventHandler {
private:
	View* view;
	std::queue<Event*> eventQueue;
public:
	void add(Event* event);
	void setView(View *view);
  	bool empty();
  	Event* get();
};

#endif