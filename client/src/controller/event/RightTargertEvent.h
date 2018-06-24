#ifndef _RIGHT_TARGET_EVENT
#define _RIGHT_TARGET_EVENT

#include "../../view/WormState.h"
#include "Event.h"

class RightTargertEvent : public Event {
private:
	WeaponId idWeapon;
public:
	RightTargertEvent(int idWeapon);
	void process();
};


#endif