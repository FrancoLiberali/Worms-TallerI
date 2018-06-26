#include "RightTargertEvent.h"
#include <iostream>

RightTargertEvent::RightTargertEvent(int idWeapon){
    this->idWeapon = static_cast<WeaponId>(idWeapon);
}

void RightTargertEvent::process(){
    WormView* worm = view->getWormView(model->getIdWormSelected());
    worm->useTelederigido();
}