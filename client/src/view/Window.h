#ifndef _WINDOW_H
#define _WINDOW_H


#include <SDL2/SDL.h>

class Window {
protected:
	SDL_Window* window;
private:
	SDL_Renderer* render;
	int width;
	int height; 
public:
	Window(int width, int height);
	~Window();
	SDL_Renderer* getRender();
	SDL_Window* getWindow();
	int getWidth();
	int getHeight();
	void update();
	void fill(int r, int g, int b, int alpha);
    void fill();
    void renderWindow();
};

#endif