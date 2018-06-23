#ifndef _GREEN_GRENADE_BULLET_VIEW_H
#define _GREEN_GRENADE_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class GreenGrenadeView : public BulletView{

public:
    GreenGrenadeView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    virtual void updatePos(int x, int y, int angle);
    virtual void update();
};

#endif