#include "Window.h"
#include <SDL2/SDL_image.h>
#include "SdlException.h"

Window::Window(int width, int height):width(width), height(height){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("WORMS",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
							width, height,SDL_WINDOW_SHOWN);
	if (window == NULL)
		throw SdlException("Error al crear la ventana\n", SDL_GetError());
	
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == NULL)
		throw SdlException("Error al crear el render\n", SDL_GetError());	

	//SDL_SetRenderDrawColor(render, 0x33, 0x33, 0x33, 0xFF);
	this->fill();
}

Window::~Window(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Window::getRender(){
	return render;
}

SDL_Window* Window::getWindow(){
	return window;
}

int Window::getWidth(){
	return width;
}

int Window::getHeight(){
	return height;
}

void Window::update(){
	SDL_UpdateWindowSurface(window);
}

void Window::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(render, r, g, b, alpha);
    SDL_RenderClear(render);
}

void Window::fill() {
    this->fill(0x33,0x33,0x33,0xFF);
}

void Window::renderWindow() {
    SDL_RenderPresent(render);
}