#include <iostream>

#include "WormWeaponEvent.h"


WormWeaponEvent::WormWeaponEvent(int idWeapon){
    weaponId = static_cast<WeaponId>(idWeapon);
}
	
void WormWeaponEvent::process(){
	WormView* wormView = view->getWormView(model->getIdWormSelected());
	wormView->selectWeapon(weaponId);
}