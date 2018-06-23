#ifndef _WORM_MOVE_EVENT
#define _WORM_MOVE_EVENT

#include "Event.h"

class WormMoveEvent : public Event {
private:
	int wormID;
	int x, y, dir, angle;
public:
	WormMoveEvent(int id, int x, int y, int dir, int angle);
	void process();
};

#endif