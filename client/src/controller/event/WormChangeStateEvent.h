#ifndef _WORM_CHANGE_STATE_EVENT
#define _WORM_CHANGE_STATE_EVENT

#include "Event.h"
#include "../../view/WormState.h"

class WormChangeStateEvent : public Event {
private:
	int wormID;
	WormState newState;
public:
	WormChangeStateEvent(int id, int state);
	void process();
};

#endif