#ifndef _PANEL_INFO_VIEW_H
#define _PANEL_INFO_VIEW_H

#include "TextView.h"

class PanelInfo {
private:
    TextView textTurn;
    TextView textWind;
    SDL_Color colorText;
public:
    PanelInfo();
    void setTextTun(std::string text);
    void setTextWind(std::string text);
    void draw(SDL_Renderer* renderer);
    void setColor(SDL_Color color);
};
#endif