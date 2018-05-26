#include "View.h"

#include <iostream>

View::View(EventHandler& eventHandler, int w, int h)
		: window(w,h), eventHandler(eventHandler), open(true){
	window.fill();
	this->init();
	window.renderWindow();
	


}

void View::init(){
	/*No deberia estar acá. Aqui se construye todos los sprites iniciales:
	  escenario, worms, armas, etc.
	*/
	/*LTexture wormTexture(window);
	if (!wormTexture.loadFromFile("wwalk.png"))
		std::cout<< "no cargo la imagen" << std::endl;
	wormTexture.render(120,200);*/
	Escenario escenario(window);
	escenario.draw();

}

View::~View(){}

bool View::isOpen(){
	return open;
}

void View::close(){
	open = false;
}

void View::update(){
	while (!eventHandler.empty()){
		std::string mensaje = eventHandler.get();
		this->procesar(mensaje);
	}
}

void View::procesar(std::string msg){
	std::cout << "procesar " << msg << std::endl;
}
