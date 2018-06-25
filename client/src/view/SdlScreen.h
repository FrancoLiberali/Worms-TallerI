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
	std::string title;
    int width;
	int height;
public:
	SdlScreen();
   	~SdlScreen();
	//inicia la ventna principal y el renderer
	void init(const char* title, int xpos, int ypos, int width,
			int height, int flags);
	//limpia el renderer
	void clear();
	//presenta el renderer en la ventna
	void render();
	//rellena o limpia la ventana
	void fill();
	//geters
	int getWidth();
	int getHeight();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	int getXCenter();
	int getYCenter();
};

#endif 