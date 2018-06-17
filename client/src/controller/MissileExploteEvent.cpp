#include "MissileExploteEvent.h"

MissileExploteEvent::MissileExploteEvent(int idMissile)
    :idMissile(idMissile){}
void MissileExploteEvent::process(){
    BulletView* bullet = view->getBulletView(idMissile);
    bullet->detonate();
}