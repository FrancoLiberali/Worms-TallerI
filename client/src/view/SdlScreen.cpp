#include "SdlScreen.h"


SdlScreen::SdlScreen() {
}

SdlScreen::~SdlScreen(){
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(renderer);
    IMG_Quit();
	SDL_Quit();
}

void SdlScreen::init(const char* title, int xpos, int ypos, int width,
			int height, int flags){
	this->title = title;
    this->height = height;
    this->width = width;

	m_pWindow = SDL_CreateWindow(title, xpos, ypos,	width, height, flags);
    if(m_pWindow == NULL)
		throw SdlException("Error al crear la ventana\n", SDL_GetError());

    renderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);	

    if (renderer == NULL)
		throw SdlException("Error al crear el render\n", SDL_GetError());

    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
}

void SdlScreen::clear(){
	SDL_RenderClear(renderer); // clear the renderer to the draw color
}	

void SdlScreen::render(){
	SDL_RenderPresent(renderer); // draw to the screen
}

void SdlScreen::fill() {
 	SDL_SetRenderDrawColor(renderer, 0x33,0x33,0x33,0xFF);
    clear();
}

SDL_Renderer* SdlScreen::getRenderer(){
	return renderer;
}

SDL_Window* SdlScreen::getWindow(){
	return m_pWindow;
}

int SdlScreen::getWidth(){
    return width;
}

int SdlScreen::getHeight(){
    return height;
}

int SdlScreen::getXCenter(){
	return width/2;
}
int SdlScreen::getYCenter(){
	return height/2;
}
