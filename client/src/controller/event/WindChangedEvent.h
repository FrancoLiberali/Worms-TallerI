#ifndef _WIND_CHANGED_EVENT
#define _WIND_CHANGED_EVENT

#include "Event.h"

class WindChangedEvent : public Event {
private:
	int windSpeed;
public:
	WindChangedEvent(int windSpeed);
	void process();
};

#endif