#ifndef _BAZOOKA_BULLET_VIEW_H
#define _BAZOOKA_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class BazookaView : public BulletView{

public:
    BazookaView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    virtual void updatePos(int x, int y, int angle);
    virtual void update();
};

#endif