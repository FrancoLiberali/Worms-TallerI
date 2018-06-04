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

	/*WormView worm1;
	worm.load(100, 200, &window);
	this->worms.emplace(1, std::move(worm1));

	WormView worm2;
	worm.load(500, 100, &window);
	this->worms.emplace(2, std::move(worm2));*/


}

View::~View(){
	for (auto& it: worms){
		//delete it.second;
	}
}

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
		Event*  event = eventHandler.get();
		//this->procesar(mensaje);
		SDL_Delay(100);
		window.fill();
		escenario.draw();
		event->process();
		delete event;
		worm.update();
		/*for (auto& w: worms){
			w.second.update();
		}*/
		window.renderWindow();
	}
	worm.update();
	/*for (auto& w: worms){
			w.second.update();
	}*/
	window.renderWindow();
}

void View::procesar(std::string msg){
	std::cout << "procesar " << msg << std::endl;
}

WormView* View::getWormView(int id){
	std::cout << "ID-WORM" << id << std::endl;
	//return &this->worms[id];
	return &worm;
}
