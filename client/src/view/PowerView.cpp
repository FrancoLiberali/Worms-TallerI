#include "PowerView.h"
#include <iostream>

#define FACTOR 2

#define X_POWER 300
#define Y_POWER 500

PowerView::PowerView():ballow(false){

	SDL_Color white = {255,0,0};
	this->label.setText("Poder", white);
	this->rect.w = 1;
}

void PowerView::setScreen(SdlScreen* screen){
    this->screen = screen;
}


void PowerView::update(){
    if(ballow){
		this->rect.w += FACTOR ;
	}
}

void PowerView::setPos(int x, int y){
    posx = x;
    posy = y;
}

void PowerView::clean(){
    this->rect.w = 1;
}


void PowerView::allow(){
	this->ballow = true;
}

void PowerView::deny(){
	this->ballow = false;
}

void PowerView::draw(){
    if (!ballow)
        return;
    int margin = 5;
    int heightBarProgress = 15;
    rect.x = X_POWER;
    rect.y = Y_POWER + 20;
    rect.h = heightBarProgress - margin;
    SDL_Color color = {255, 0 , 255};
    TextureManager::Instance().drawFillRect(screen->getRenderer(), rect, color);
    this->label.draw(screen->getRenderer(), X_POWER , Y_POWER);
}