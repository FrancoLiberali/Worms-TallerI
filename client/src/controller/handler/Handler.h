#ifndef _HANDLER_H
#define _HANDLER_H

#include "SDL2/SDL_events.h"

class Handler {
 public:
  virtual void handle(SDL_Event *e, EventHandler &eventHandler) = 0;
};

#endif 
