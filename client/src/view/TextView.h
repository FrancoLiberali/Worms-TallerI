#ifndef _TEXT_VIEW_H_
#define _TEXT_VIEW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string.h>
#include "TextureManager.h"
#include "FontManager.h"
#include "TextManager.h"


class TextView{
private:	
	SDL_Texture* mTexture;
	Tfont font;
	std::string text;
	SDL_Color textColor;
	int mWidth;
	int mHeight;

public:

	TextView();
	~TextView();
	void setFont(Tfont font);
	bool setText( std::string textureText, SDL_Color textColor);
	void free();
	void setColor( Uint8 red, Uint8 green, Uint8 blue );
	void setBlendMode( SDL_BlendMode blending );
	void setAlpha( Uint8 alpha );
	void draw(SDL_Renderer * gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
	int getWidth();
	int getHeight();
};

#endif