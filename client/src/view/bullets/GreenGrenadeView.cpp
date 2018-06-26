#include "GreenGrenadeView.h"


GreenGrenadeView::GreenGrenadeView(int id, int dir, int posx, int posy, int angle, 
    SdlScreen& screen, Camera& camera):BulletView(id,dir,posx, posy,angle, screen, camera){
    this->spriteBullet = SpriteConfigurator::Instance().get("bullet_ggrenade");
	this->spriteExplosion = SpriteConfigurator::Instance().get("explotion");
    this->explotionSound = EXPLOTION;
}

void GreenGrenadeView::updatePos(int x, int y, int angle){
    posx = x;
    posy = y;
    camera.updateCenter(getCenterX(), getCenterY());
    this->angle = angle;
}

void GreenGrenadeView::update(){
    if (detonated && !currentSprite->isLastFrame())
        currentSprite->update();
    draw();
}
