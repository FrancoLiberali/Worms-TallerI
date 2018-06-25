#ifndef _BULLET_VIEW_H
#define _BULLET_VIEW_H

#include "../Sprite.h"
#include "../SdlScreen.h"
#include "../Camera.h"
#include "../../sound/SoundManager.h"

/**
* @class BulletView
* clase abstracta que representa a la vista del misil de un arma.
* Toda nueva vista de un misil debe heredar de esta clase.
*/

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
    virtual void updatePos(int x, int y, int angle) = 0;
    virtual void update() = 0;
    void detonate();
    bool isIdBullet(int id);
    bool isDetonateDone();
    void disableCamera();
    void draw();

};
#endif