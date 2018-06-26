#include "WatchView.h"
#include "../manager/TextureManager.h"
#include "../manager/TextManager.h"

WatchView::WatchView(SdlScreen& screen):seconds(INIT_TIME), screen(screen){
    title.setText("TIEMPO");
  

}
WatchView::~WatchView(){
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
    timeView.setText(std::to_string(seconds));
    seconds--;
}