#ifndef _BACKGROUND_EVENT_H
#define _BACKGROUND_EVENT_H

#include "Event.h"

class BackgroundEvent : public Event {
private:
    std::string name;
public:
	BackgroundEvent(std::string name);
	void process();
};

#endif