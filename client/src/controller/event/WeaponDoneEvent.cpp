#include "WeaponDoneEvent.h"
#include <iostream>


WeaponDoneEvent::WeaponDoneEvent(int idWeapon){
    this->idWeapon = static_cast<WeaponId>(idWeapon);
}

void WeaponDoneEvent::process(){
    //hacer algo con la vista
    printf("se acabo el arma %i\n", idWeapon);
    view->weaponDone(idWeapon);
}