#ifndef _SECOND_EVENT
#define _SECOND_EVENT

#include "../../view/WormState.h"
#include "Event.h"

class SecondEvent : public Event {
public:
	SecondEvent();
	void process();
};


#endif