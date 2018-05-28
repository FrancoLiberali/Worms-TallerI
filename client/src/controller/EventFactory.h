#ifndef _EVENT_FACTORY
#define _EVENT_FACTORY 

#include "EventType.h"
#include "Event.h"
#include <sstream>

class EventFactory{
public:
	static Event* createEvent(const EventType& type,  
		std::stringstream &ss); 
};
#endif