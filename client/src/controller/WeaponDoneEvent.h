#ifndef _WEAPON_DONE_EVENT
#define _WEAPON_DONE_EVENT

#include "Event.h"

class WeaponDoneEvent : public Event {
private:
	int idWeapon;
public:
	WeaponDoneEvent(int idWeapon);
	void process();
};

#endif