#ifndef _SDL_SCREEN_H
#define _SDL_SCREEN_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "SdlException.h"

class SdlScreen {
private:
    SDL_Window* m_pWindow;
	SDL_Renderer* renderer;
	SDL_Texture* mTexture;
	std::string title;
    int width;
	int height;
public:
	SdlScreen();
   	~SdlScreen();
	void init(const char* title, int xpos, int ypos, int width,
			int height, int flags);
	void clear();
	void render();
	void fill();
	int getWidth();
	int getHeight();
	void setState(std::string string_state);
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	int getXCenter();
	int getYCenter();
};

#endif 