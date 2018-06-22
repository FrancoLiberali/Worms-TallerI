#ifndef _AIR_MISSILE_BULLET_VIEW_H
#define _AIR_MISSILE_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class AirMissileView : public BulletView{

public:
    AirMissileView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    void updatePos(int x, int y, int angle);
    void update();
};

#endif