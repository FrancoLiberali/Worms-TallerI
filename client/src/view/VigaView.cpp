#include "VigaView.h"

#define OFFSET 3

VigaView::VigaView(int posX, int posY, int angle, SdlScreen& screen) 
        : x(posX), y(posY), angle(angle), screen(screen){
}

VigaView::~VigaView(){

}

void VigaView::draw(){
    TextureManager::Instance().draw("viga", getXCenter(), getYCenter(), angle, screen.getRenderer());
}

int  VigaView::getXCenter(){
    SDL_Texture* viga = TextureManager::Instance().getTexture("viga");
    int w = 0, h = 0;
    SDL_QueryTexture(viga,NULL,NULL, &w, &h);
    return (x - (w/2));
}

int VigaView::getYCenter(){
    SDL_Texture* viga = TextureManager::Instance().getTexture("viga");
    int w = 0, h = 0;
    SDL_QueryTexture(viga,NULL,NULL, &w, &h);
    return (y-(h/2));
}