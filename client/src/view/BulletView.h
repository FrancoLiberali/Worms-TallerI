#ifndef _BULLET_VIEW_H
#define _BULLET_VIEW_H

#include "Sprite.h"
#include "SdlScreen.h"
#include "Camera.h"
#include "../sound/SoundManager.h"

class BulletView {
private:
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
    SoundId explotioSound;
	bool detonated;
    void draw();
    int getCenterX();
    int getCenterY();
public:
    BulletView(int id, int dir, int posx, int posy, int angle,
            SdlScreen& screen, Camera& camera);
    void setSpriteBullet(Sprite spriteBullet);
    void setSpriteExplosion(Sprite spriteExplosion);
    void setExplotionSound(SoundId idSound);
    void updatePos(int x, int y, int angle);
    void update();
    void detonate();
    bool isIdBullet(int id);
    bool isDetonateDone();
};
#endif