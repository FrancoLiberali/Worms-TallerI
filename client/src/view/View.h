#ifndef _VIEW_H
#define _VIEW_H
#include "../controller/EventHandler.h"
#include "Window.h"
#include "Texture.h"
#include "Escenario.h"
#include "WormView.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

/*Contiene todo referante al dibujado de los objetos*/
class View {
private:
	Window window;
	EventHandler& eventHandler;
	WormView worm;
	bool open;
	void procesar(std::string mensaje);
	void init();
public:
	View(EventHandler& eventHandler, int w, int h);
	~View();
	bool isOpen();
	void update();
	void close();
	//para pruebas
	Window& getWindow(){return window;}

};

#endif
