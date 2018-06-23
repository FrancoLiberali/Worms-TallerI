#include <iostream>

#include "WormWeaponEvent.h"


WormWeaponEvent::WormWeaponEvent(int wormId, int idWeapon)
	:wormId(wormId){
    weaponId = static_cast<WeaponId>(idWeapon);
}
	
void WormWeaponEvent::process(){
	WormView* wormView = view->getWormView(wormId);
	wormView->selectWeapon(weaponId);
}