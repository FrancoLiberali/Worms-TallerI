#ifndef _DYNAMITE_BULLET_VIEW_H
#define _DYNAMITE_BULLET_VIEW_H

#include "BulletView.h"

class BulletView;

class DynamiteView : public BulletView{
private:
    SoundId waitSound;
    bool partialExplote;
public:
    DynamiteView(int id, int dir, int posx, int posy, int angle, 
        SdlScreen& screen, Camera& camera);
    virtual void updatePos(int x, int y, int angle);
    virtual void update();
};

#endif