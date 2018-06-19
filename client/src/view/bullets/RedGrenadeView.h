#ifndef _RED_GRENADE_BULLET_VIEW_H
#define _RED_GRENADE_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class RedGrenadeView : public BulletView{

public:
    RedGrenadeView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    void updatePos(int x, int y, int angle);
    void update();
};

#endif