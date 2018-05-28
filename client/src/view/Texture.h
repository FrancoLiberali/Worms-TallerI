#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Window.h"

class LTexture {
public:
	//Initializes variables
	LTexture();
	LTexture(Window& window);

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile( std::string path );
	bool loadFromFile( std::string path, Window& window);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );
	
	//Renders texture at given point
	void render( int x, int y, double angle = 0, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Renderer* gRenderer;
	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif