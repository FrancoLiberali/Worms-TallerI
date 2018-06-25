#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <string>

/*
* @class FontManager
* Usa el patrón singletón, manejador de fuentes, carga las fuentes.
*/
class FontManager
{
private:
	std::map<std::string, TTF_Font*> fonts;
	SDL_Renderer* renderer;
public:

	static FontManager& Instance(){
			static FontManager instance;
			return instance;
	}

	void init(SDL_Renderer* renderer);

	void openFont(std::string id, std::string path, int size);

	TTF_Font* getFont(std::string& fontId);

	SDL_Renderer* getRenderer();
	
	void closeFonts();
};

#endif
