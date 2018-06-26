#ifndef _WORM_WEAPON_EVENT
#define _WORM_WEAPON_EVENT

#include "Event.h"

#include "../../view/WormStateAndWeapon.h"

/*@class: WormWeaponEvent
* Evento del cambio de arma de un gusano. La id del arma debe ser válida.
*/
class WormWeaponEvent : public Event {
private:
    WeaponId weaponId;
public:
	WormWeaponEvent(int idWeapon);
	void process();
};

#endif