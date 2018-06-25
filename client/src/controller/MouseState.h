#ifndef _MOUSE_STATE_H
#define _MOUSE_STATE_H

#include <SDL2/SDL_events.h>
#include "EventHandler.h"

/*@class: MouseState
* Verifica el estado del mouse, si hay que mover la camara o no.
*/
class MouseState {
private:
    int x;
    int y;
public:
    MouseState();
    void handle(SDL_Event& e, EventHandler& EventHandler);
};

#endif