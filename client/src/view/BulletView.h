#ifndef _BULLET_VIEW_H
#define _BULLET_VIEW_H

#include "newView/Sprite.h"
#include "newView/SdlScreen.h"

class BulletView {
private:
    int id;
    int posx; 
    int posy;
    int angle;

    Sprite* currentSprite;
    SDL_RendererFlip flip;
    SdlScreen& screen;

	Sprite spriteBullet;
	Sprite spriteExplosion;
	bool detonated;
    void draw();
    int getCenterX();
    int getCenterY();
public:
    BulletView(int id, int dir, int posx, int posy, int angle, SdlScreen& screen);
    void setSpriteBullet(Sprite spriteBullet);
    void setSpriteExplosion(Sprite spriteExplosion);
    void updatePos(int x, int y, int angle);
    void update();
    void detonate();
    bool isIdBullet(int id);
    bool isDetonateDone();
};
#endif