#ifndef _ESCENARIO_H
#define _ESCENARIO_H 

#include "Window.h"
#include "Texture.h"

class Escenario{
	Window& window;
public:
	Escenario(Window& window);
	void draw();
	
};
#endif