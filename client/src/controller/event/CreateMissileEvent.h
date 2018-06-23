#ifndef _CREATE_MISSILE_EVENT_H
#define _CREATE_MISSILE_EVENT_H

#include "Event.h"
#include "../../view/WormState.h"

class CreateMissileEvent : public Event {
private:
    int id;
    WeaponId weaponId;
    int dir;
	int posx;
    int posy;
    int angle;
    mainView& view;
public:
	CreateMissileEvent(int id, int idWeapon, int dir, int x, int y, int angle, mainView& view);
	void process();
};

#endif