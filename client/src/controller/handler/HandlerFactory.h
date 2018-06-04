#ifndef _HANDLER_FACTORY_H
#define _HANDLER_FACTORY_H

#include "Handler.h"
#include "SDL2/SDL_events.h"

class HandlerFactory {
 public:
  static Handler* get(SDL_Event *e);
};

#endif
