#ifndef _WATCH_VIEW_H
#define _WATCH_VIEW_H

#include <SDL2/SDL.h>
#include "TextView.h"
#include "SdlScreen.h"
#define INIT_TIME 60

/*
* @class WatchView
* Muestra el paso del tiempo del juego por turno;
*/
class WatchView{
private:
    TextView title;
    TextView timeView;
    SdlScreen&  screen;
    int seconds;
public:
    WatchView(SdlScreen& screen);
    ~WatchView();
    void start();
    void update(SDL_Renderer* render);
    void draw();
};

#endif