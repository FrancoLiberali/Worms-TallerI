#ifndef _WORM_WEAPON_EVENT
#define _WORM_WEAPON_EVENT

#include "Event.h"
#include "../view/WormState.h"

class WormWeaponEvent : public Event {
private:
	int wormId;
    WeaponId weaponId;
public:
	WormWeaponEvent(int wormId, int idWeapon);
	void process();
};

#endif