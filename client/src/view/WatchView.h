#ifndef _WATCH_VIEW_H
#define _WATCH_VIEW_H

#include <SDL2/SDL.h>
#include "TextView.h"
#include "SdlScreen.h"
#define INIT_TIME 60

class WatchView{
private:
    TextView title;
    //TextView time;
    SdlScreen&  screen;
    SDL_Texture* timeTexture;
    int seconds;
public:
    WatchView(SdlScreen& screen);
    ~WatchView();
    void start();
    void update(SDL_Renderer* render);
    void draw();
};

#endif