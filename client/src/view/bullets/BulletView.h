#ifndef _BULLET_VIEW_H
#define _BULLET_VIEW_H

#include "../Sprite.h"
#include "../SdlScreen.h"
#include "../Camera.h"
#include "../../sound/SoundManager.h"

class BulletView {
protected:
    int id;
    int posx; 
    int posy;
    int angle;

    Sprite* currentSprite;
    SDL_RendererFlip flip;
    SdlScreen& screen;
    Camera& camera;

    Sprite spriteBullet;
	Sprite spriteExplosion;
    SoundId explotionSound;
	bool detonated;
    bool isOnCamera;
    int getCenterX();
    int getCenterY();
public:
    BulletView(int id, int dir, int posx, int posy, int angle,
            SdlScreen& screen, Camera& camera);
    void setSpriteBullet(Sprite spriteBullet);
    void setSpriteExplosion(Sprite spriteExplosion);
    void setExplotionSound(SoundId idSound);
    virtual void updatePos(int x, int y, int angle);
    virtual void update();
    void detonate();
    bool isIdBullet(int id);
    bool isDetonateDone();
    void disableCamera();
    void draw();

};
#endif