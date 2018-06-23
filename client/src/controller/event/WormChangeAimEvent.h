#ifndef _WORM_CHANGE_AIM_EVENT
#define _WORM_CHANGE_AIM_EVENT

#include "Event.h"

class WormChangeAimEvent : public Event {
private:
	int wormId;
    int delta;
public:
	WormChangeAimEvent(int wormId, int delta);
	void process();
};

#endif