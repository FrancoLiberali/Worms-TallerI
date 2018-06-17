#include <iostream>

#include "WormWeaponEvent.h"

WormWeaponEvent::WormWeaponEvent(int wormId, int idWeapon)
	:wormId(wormId){
    weaponId = static_cast<WeaponId>(idWeapon);
}
	
void WormWeaponEvent::process(){
    if (weaponId == NO_WEAPON) //ENCONTRAR EL BUG PARA QUE ANDE 
        return;
	WormView* wormView = view->getWormView(wormId);
	wormView->selectWeapon(weaponId);
}