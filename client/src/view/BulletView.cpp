#include "BulletView.h"
#include "newView/TextureManager.h"

BulletView::BulletView(int id, int dir, int posx, int posy, int angle, SdlScreen& screen)
    :id(id), posx(posx), posy(posy), angle(angle), detonated(false), screen(screen){
    
    this->flip = (dir == 1)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    currentSprite =&this->spriteBullet; 
}

void BulletView::setSpriteBullet(Sprite spriteBullet){
    this->spriteBullet = spriteBullet;
}

void BulletView::setSpriteExplosion(Sprite spriteExplosion){
    this->spriteExplosion = spriteExplosion;
}
void BulletView::updatePos(int x, int y, int angle){
    posx = x;
    posy = y;
    this->angle = angle;
}

void BulletView::update(){
    if (detonated && !currentSprite->isLastFrame())
        currentSprite->update();
    draw();
}

void BulletView::detonate(){
    currentSprite = &spriteExplosion;
    detonated = true;
}

bool BulletView::isIdBullet(int id){
    return this->id == id;
}

bool BulletView::isDetonateDone(){
    return detonated;
}

void BulletView::draw(){
    if (currentSprite->isLastFrame())
        return;
    TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										getCenterX(), getCenterY(), angle, 
										currentSprite->getWidth(),
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										0, screen.getRenderer(), false, flip);
}

int BulletView::getCenterX(){
	return this->posx-(currentSprite->getWidth()/2);
}

int BulletView::getCenterY(){
    return this->posy-(currentSprite->getHeight()/2);
}