#include "MissileMoveEvent.h"
#include <iostream>

MissileMoveEvent::MissileMoveEvent(int idMissile, int posx, int posy, int angle)
    :idMissile(idMissile), posx(posx), posy(posy), angle(angle){}

void MissileMoveEvent::process(){
    BulletView* bullet = view->getBulletView(idMissile);
    bullet->updatePos(posx, posy, angle);
}
