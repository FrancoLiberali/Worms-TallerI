#include "AirMissileView.h"
#include "../../sound/SoundManager.h"
#include "../SpriteConfigurator.h"
#include <iostream>

AirMissileView::AirMissileView(int id, int dir, int posx, int posy, int angle, 
    SdlScreen& screen, Camera& camera):BulletView(id,dir,posx, posy,angle, screen, camera){
    this->spriteBullet = SpriteConfigurator::Instance().get("bullet_airmisl");
	this->spriteExplosion = SpriteConfigurator::Instance().get("explotion");
    this->explotionSound = EXPLOTION;
}

void AirMissileView::updatePos(int x, int y, int angle){
    posx = x;
    posy = y;
    camera.updateCenter(getCenterX(), getCenterY());
    angle = angle;
    printf("Pos %i, %i\n", posx, posy);
}

void AirMissileView::update(){
    if (detonated && !currentSprite->isLastFrame())
        currentSprite->update();
    draw();
}
