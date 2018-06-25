#ifndef _CREATE_MISSILE_EVENT_H
#define _CREATE_MISSILE_EVENT_H

#include "Event.h"
#include "../../view/WormStateAndWeapon.h"

/*@class: CreateMissileEvent
* Evento que responde a la creación de un misil del server
*/
class CreateMissileEvent : public Event {
private:
    int id;
    WeaponId weaponId;
    int dir;
	int posx;
    int posy;
    int angle;
public:
	CreateMissileEvent(int id, int idWeapon, int dir, int x, int y, int angle);
	void process();
};

#endif