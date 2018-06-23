#include "MouseState.h"
#include "event/CameraMoveEvent.h"

#define W_WIDHT 800
#define W_HEIGHT 600

MouseState::MouseState(){}

void MouseState::handle(SDL_Event& e, EventHandler& eventHandler){
    SDL_GetMouseState(&x, &y);
    if (x < 10 || x > W_WIDHT-10 || y < 10 || y > W_HEIGHT-10) {
        eventHandler.add(new CameraMoveEvent(x, y));
  }
}