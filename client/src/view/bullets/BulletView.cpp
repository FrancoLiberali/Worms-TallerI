#include "BulletView.h"

BulletView::BulletView(int id, int dir, int posx, int posy, int angle, SdlScreen& screen, Camera& camera)
    :id(id), posx(posx), posy(posy), angle(angle), detonated(false), screen(screen), camera(camera){
    
    this->flip = (dir == 1)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    currentSprite =&this->spriteBullet; 
}

void BulletView::disableCamera(){
    this->isOnCamera = false;
}

void BulletView::detonate(){
    currentSprite = &spriteExplosion;
    detonated = true;
    SoundManager::Instance().stopAllSounds();
    SoundManager::Instance().playSound(explotionSound);
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
										getCenterX() - camera.getX(),
                                        getCenterY() - camera.getY(), angle, 
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