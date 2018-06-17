#include "CreateMissileEvent.h"


CreateMissileEvent::CreateMissileEvent(int id, int idWeapon, int dir, 
    int x, int y, int angle, mainView& view):id(id), dir(dir), posx(x), 
    posy(y), angle(angle), view(view){
        weaponId = static_cast<WeaponId>(idWeapon);   
    }

void CreateMissileEvent::process(){
    view.addMissile(id, weaponId, dir, posx, posy, angle);
}