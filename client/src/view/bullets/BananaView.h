#ifndef _BANANA_BULLET_VIEW_H
#define _BANANA_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class BananaView : public BulletView{

public:
    BananaView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    void updatePos(int x, int y, int angle);
    void update();
};

#endif