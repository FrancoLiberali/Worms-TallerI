#ifndef _FRAGMENT_BULLET_VIEW_H
#define _FRAGMENT_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class FragmentView : public BulletView{

public:
    FragmentView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    virtual void updatePos(int x, int y, int angle);
    virtual void update();
};

#endif