#include "FontManager.h"
#include "../exception/SdlException.h"
#include "../../config.h"

void FontManager::init(SDL_Renderer * renderer){
	this->renderer = renderer;
	if (TTF_Init() == -1)
		throw SdlException("No se puedo abrir TTF", TTF_GetError());
}

void FontManager::openFont(std::string id, std::string path, int size){
	TTF_Font * font = TTF_OpenFont(path.c_str(), size);
	if (!font)
		throw SdlException("No hay fuente SDL_ttf Error", TTF_GetError());
	fonts[id] = font;
}

TTF_Font* FontManager::getFont(std::string& fontId){
	if (fonts.find(fontId) == fonts.end())
		return NULL;
	return fonts[fontId];;
}

void FontManager::closeFonts(){
	for (auto& it : fonts){
		TTF_CloseFont(it.second);
	}
	fonts.clear();
}

SDL_Renderer* FontManager::getRenderer() {
	return this->renderer;
}
