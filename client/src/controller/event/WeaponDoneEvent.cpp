#include "WeaponDoneEvent.h"
#include <iostream>


WeaponDoneEvent::WeaponDoneEvent(int idWeapon){
    this->idWeapon = static_cast<WeaponId>(idWeapon);
}

void WeaponDoneEvent::process(){
    view->weaponDone(idWeapon);
}