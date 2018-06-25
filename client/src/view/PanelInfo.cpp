#include "PanelInfo.h"
#include "../manager/TextureManager.h"
#include "../manager/TextManager.h"

PanelInfo::PanelInfo(){
    this->colorText = {255, 0, 0};
}

void PanelInfo::setTextTun(std::string text){
    textTurn.setText(text);
}
void PanelInfo::setTextWind(std::string text){
    textWind.setText(text); 
}

void PanelInfo::draw(SDL_Renderer* renderer){
    TextureManager::Instance().draw("message", 0 , 0, 0, renderer, 
            SDL_FLIP_NONE,210, 70 );
    textTurn.draw(renderer, 15, 18);
    textWind.draw(renderer, 15, 38);
}

void PanelInfo::setColor(SDL_Color color){
    this->colorText = color;
}