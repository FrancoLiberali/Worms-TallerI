#ifndef _UTIL_H
#define _UTIL_H

#include <SDL2/SDL.h>


class Util{
public:
    static SDL_Color getColor(int ud);
    static void getDimentionTexture(SDL_Texture* texture, int* w, int* h);
};

#endif