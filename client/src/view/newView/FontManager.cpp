#include "FontManager.h"
#include "SdlException.h"

void FontManager::init(SDL_Renderer * renderer)
{
	this->renderer = renderer;
	if (TTF_Init() == -1)
		throw SdlException("No se puedo abrir TTF", TTF_GetError());
	openFonts();
}

void FontManager::openFonts()
{
	TTF_Font * aFont = TTF_OpenFont( "res/font/arial.ttf", 11 );
	if (!aFont)
		throw SdlException("No hay fuente SDL_ttf Error", TTF_GetError());
	map["arial"] = aFont;
}

TTF_Font* FontManager::getFont(std::string fontId){
	if (map.find(fontId) == map.end())
		return NULL;
	return map[fontId];;
}

void FontManager::closeFonts(){

	std::map<std::string, TTF_Font*>::iterator iter;
	for (iter = map.begin(); iter!=map.end(); ++iter){
		TTF_CloseFont(iter->second);
	}
	map.clear();
}