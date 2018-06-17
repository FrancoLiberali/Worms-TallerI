#ifndef _MISSILE_MOVE_EVENT
#define _MISSILE_MOVE_EVENT

#include "Event.h"

class MissileMoveEvent : public Event {
private:
	int idMissile;
	int posx, posy, angle;
public:
    MissileMoveEvent(int idMissile, int posx, int posy, int angle);
	void process();
};

#endif