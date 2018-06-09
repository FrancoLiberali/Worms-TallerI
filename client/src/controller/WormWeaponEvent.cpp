#include <iostream>

#include "WormWeaponEvent.h"

WormWeaponEvent::WormWeaponEvent(int wormId, int idWeapon)
	:wormId(wormId){
    switch (idWeapon) {
        case 0 : weaponId = NO_WEAPON; break;
        case 1 : weaponId = BAZOOKA; break;
        case 2 : weaponId = MORTERO; break;
        case 3 : weaponId = G_GRENADE; break;
        case 4 : weaponId = R_GRENADE; break;
        case 5 : weaponId = BANANA; break;
        case 6 : weaponId = HOLY; break;
        case 7 : weaponId = DYNAMITE; break;
        case 8 : weaponId = BATE; break;
        case 9 : weaponId = AIRATTACK; break;
        case 10 : weaponId = TELEPORT; break;
    }
}
	
void WormWeaponEvent::process(){
	WormView* wormView = view->getWormView(wormId);
	wormView->selectWeapon(weaponId);
}