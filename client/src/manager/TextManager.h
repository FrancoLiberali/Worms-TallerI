#ifndef _TEXT_MANAGER_H
#define _TEXT_MANAGER_H

#include <map>
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "../../config.h"
#include "FontManager.h"

enum Tfont{
	Arial16,
	Arial12,
};

/*
*@class TextManager
* Singletón, manejador de todo la escritura de texto en las ventanas.
*/
class TextManager{
private:
	SDL_Renderer* renderer;
	struct stFont{
		std::string idFont;
		int ancho, alto;
		int anchoLetra, altoLetra;
	};
	std::map<std::string, stFont> font_map;
	stFont font;
public:
	static TextManager & Instance(){
			static TextManager theTextManager;
			return theTextManager;
	}

	void init(SDL_Renderer * renderer);
	//carga un fuente(imagen).
	void loadFont(Tfont font);
	//escribe una letra de la imagen de fuente
	void wLetter(std::string& idFont,int x, int y, char lett,SDL_Color color, int factor = 1);
	//escribe a partir de la textura de fuente que previamente se cargo.
	void write(Tfont fuente,int x, int y, std::string w,SDL_Color color, int factor = 1);
	//Escribe un textura a partir de la fuente que fue previamente cargado por el FontManager
	void write(SDL_Texture* texture, std::string& idfont, int x, int y, 
		std::string& text, SDL_Color color);
	//Devuelve una textura con el string
	SDL_Texture* createText(std::string idfont, std::string& text, SDL_Color color );
};

#endif