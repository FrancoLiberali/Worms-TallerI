#include "WatchView.h"
#include "TextureManager.h"
#include "TextManager.h"

WatchView::WatchView(SdlScreen& screen):seconds(INIT_TIME), screen(screen){
    title.setText("TIEMPO");
  

}
WatchView::~WatchView(){
    //SDL_DestroyTexture(timeTexture);
}

void WatchView::start(){
    seconds = INIT_TIME;
}

void WatchView::draw(){
    TextureManager::Instance().draw("reloj", 25, 55, 0 , screen.getRenderer());
    timeView.draw(screen.getRenderer(), 10, 75, 3);
    title.draw(screen.getRenderer(), 30, 65);
}

void WatchView::update(SDL_Renderer* renderer){
    /*SDL_Color color;
    if (seconds > 10) color = {255,225,255}; else color = {255,0,0};
    TextManager::Instance().write(timeTexture, "reloj", 20, 85, std::to_string(seconds), color);*/
    timeView.setText(std::to_string(seconds));
    seconds--;
}