#include "RedGrenadeView.h"
#include "../../sound/SoundManager.h"
#include "../SpriteConfigurator.h"


RedGrenadeView::RedGrenadeView(int id, int dir, int posx, int posy, int angle, 
    SdlScreen& screen, Camera& camera):BulletView(id,dir,posx, posy,angle, screen, camera){
    this->spriteBullet = SpriteConfigurator::Instance().get("bullet_rgrenade");
	this->spriteExplosion = SpriteConfigurator::Instance().get("explotion");
    this->explotionSound = EXPLOTION;
}

void RedGrenadeView::updatePos(int x, int y, int angle){
    posx = x;
    posy = y;
    camera.updateCenter(getCenterX(), getCenterY());
    angle = angle;
}

void RedGrenadeView::update(){
    if (detonated && !currentSprite->isLastFrame())
        currentSprite->update();
    draw();
}
