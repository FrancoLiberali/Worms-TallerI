#include "WeaponDoneEvent.h"
#include <iostream>


WeaponDoneEvent::WeaponDoneEvent(int idWeapon):idWeapon(idWeapon){

}

void WeaponDoneEvent::process(){
    //hacer algo con la vista
    printf("se acabo el arma %i\n", idWeapon);
}