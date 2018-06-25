#ifndef _BULLET_VIEW_H
#define _BULLET_VIEW_H

#include "../Sprite.h"
#include "../SdlScreen.h"
#include "../Camera.h"
#include "../../manager/SoundManager.h"
#include "../../manager/TextureManager.h"
#include "../../manager/SpriteConfigurator.h"

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
    //método virtual que actualiza la podsición de una arma
    virtual void updatePos(int x, int y, int angle) = 0;
    //método virtual que actuliza el sprite (puede agregar sonidos o efectos
    //propios de cada arma)
    virtual void update() = 0;
    //detona la vista, setea el sprite de explosión
    void detonate();
    bool isIdBullet(int id);
    bool isDetonateDone();
    //desabilita la camara
    void disableCamera();
    void draw();

};
#endif