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
	Escenario escenario(window);
	escenario.draw();

	//Cargamos al worm pasamos la posicion inicial
	worm.load(100,200, &window);

}

View::~View(){}

bool View::isOpen(){
	return open;
}

void View::close(){
	open = false;
}

void View::update(){
	window.fill();
	Escenario escenario(window);
	escenario.draw();
	while (!eventHandler.empty()){
		std::string mensaje = eventHandler.get();
		this->procesar(mensaje);
	}
	worm.update();
	window.renderWindow();
}

void View::procesar(std::string msg){
	std::cout << "procesar " << msg << std::endl;
}
