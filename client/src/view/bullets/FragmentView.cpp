#include "FragmentView.h"
#include "../../sound/SoundManager.h"
#include "../SpriteConfigurator.h"


FragmentView::FragmentView(int id, int dir, int posx, int posy, int angle, 
    SdlScreen& screen, Camera& camera):BulletView(id,dir,posx, posy,angle, screen, camera){
    this->spriteBullet = SpriteConfigurator::Instance().get("bullet_fragment");
	this->spriteExplosion = SpriteConfigurator::Instance().get("explotion");
    this->explotionSound = EXPLOTION;
}

void FragmentView::updatePos(int x, int y, int angle){
    posx = x;
    posy = y;
    angle = angle;
}

void FragmentView::update(){
    if (detonated && !currentSprite->isLastFrame())
        currentSprite->update();
    draw();
}
