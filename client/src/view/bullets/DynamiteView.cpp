#include "DynamiteView.h"
#include "../../sound/SoundManager.h"
#include "../SpriteConfigurator.h"


DynamiteView::DynamiteView(int id, int dir, int posx, int posy, int angle, 
    SdlScreen& screen, Camera& camera):BulletView(id,dir,posx, posy,angle, screen, camera){
    this->spriteBullet = SpriteConfigurator::Instance().get("bullet_dynamite");
	this->spriteExplosion = SpriteConfigurator::Instance().get("explotion");
    this->explotionSound = EXPLOTION;
    this->waitSound = FUSE;
    partialExplote = false;
}

void DynamiteView::updatePos(int x, int y, int angle){
    posx = x;
    posy = y;
    angle = angle;
}

void DynamiteView::update(){
    if (!detonated){
        if (!partialExplote){   
            SoundManager::Instance().playSound(FUSE, 10, 1);
            partialExplote = true;
        }
        currentSprite->update();
    }else if (!currentSprite->isLastFrame()){
        currentSprite->update();
    }
    draw();
}
