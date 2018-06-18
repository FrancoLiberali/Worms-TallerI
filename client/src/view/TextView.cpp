#include "TextView.h"

TextView::TextView(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	this->font = Arial16;
}

TextView::~TextView(){
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void TextView::setFont(Tfont font){
	this->font = font;

}

bool TextView::setText( std::string textureText, SDL_Color textColor){	
	this->text = textureText;
	this->textColor = textColor;
	return true;
}

void TextView::setColor( Uint8 red, Uint8 green, Uint8 blue ){
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void TextView::setBlendMode( SDL_BlendMode blending ){
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void TextView::setAlpha( Uint8 alpha ){
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void TextView::draw(SDL_Renderer * gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
	TextManager::Instance().write(this->font,x, y,this->text,this->textColor);
}

int TextView::getWidth(){
	return mWidth;
}

int TextView::getHeight(){
	return mHeight;
}
