#ifndef _SDL_SCREEN_H
#define _SDL_SCREEN_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../exception/SdlException.h"
/**
* @class SdlScreen
* Wrapper para el manejo de la ventana principal, contiene la ventana 
* y el renderer únicos para el programa.
*/

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
	void restart();
};

#endif 