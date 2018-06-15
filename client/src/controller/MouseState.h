#ifndef _MOUSE_STATE_H
#define _MOUSE_STATE_H

#include <SDL2/SDL_events.h>
#include "EventHandler.h"

class MouseState {
private:
    int x;
    int y;
public:
    MouseState();
    void handle(SDL_Event& e, EventHandler& EventHandler);
};

#endif