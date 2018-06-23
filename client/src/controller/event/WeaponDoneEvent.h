#ifndef _WEAPON_DONE_EVENT
#define _WEAPON_DONE_EVENT

#include "Event.h"
#include "../../view/WormState.h"

class WeaponDoneEvent : public Event {
private:
	WeaponId idWeapon;
public:
	WeaponDoneEvent(int idWeapon);
	void process();
};

#endif