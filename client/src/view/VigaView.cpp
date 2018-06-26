#include "VigaView.h"
#include "../common/Util.h"

#define OFFSET 3

VigaView::VigaView(int posX, int posY, int angle, SdlScreen& screen,  Camera& camera) 
        : x(posX), y(posY), angle(angle), screen(screen), camera(camera){
}

VigaView::~VigaView(){

}

void VigaView::draw(){
    TextureManager::Instance().draw("viga", getXCenter()-camera.getX(),
         getYCenter()-camera.getY(), angle, screen.getRenderer());
}

int  VigaView::getXCenter(){
    SDL_Texture* viga = TextureManager::Instance().getTexture("viga");
    int w = 0, h = 0;
    Util::getDimentionTexture(viga, &w, &h);
    return (x - (w/2));
}

int VigaView::getYCenter(){
    SDL_Texture* viga = TextureManager::Instance().getTexture("viga");
    int w = 0, h = 0;
    Util::getDimentionTexture(viga, &w, &h);
    return (y-(h/2));
}