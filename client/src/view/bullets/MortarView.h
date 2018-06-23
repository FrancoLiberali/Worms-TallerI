#ifndef _MORTER_BULLET_VIEW_H
#define _MORTER_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class MortarView : public BulletView{

public:
    MortarView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    virtual void updatePos(int x, int y, int angle);
    virtual void update();
};

#endif