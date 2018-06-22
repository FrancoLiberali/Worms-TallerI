#include "BazookaView.h"
#include "../../sound/SoundManager.h"
#include "../SpriteConfigurator.h"


BazookaView::BazookaView(int id, int dir, int posx, int posy, int angle, 
    SdlScreen& screen, Camera& camera):BulletView(id,dir,posx, posy,angle, screen, camera){
    this->spriteBullet = SpriteConfigurator::Instance().get("bullet_bazooka");
	this->spriteExplosion = SpriteConfigurator::Instance().get("explotion");
    this->explotionSound = EXPLOTION;
}

void BazookaView::updatePos(int x, int y, int angle){
    posx = x;
    posy = y;
    camera.updateCenter(getCenterX(), getCenterY());
    angle = angle;
    printf("Pos %i, %i\n", posx, posy);
}

void BazookaView::update(){
    if (detonated && !currentSprite->isLastFrame())
        currentSprite->update();
    draw();
}
