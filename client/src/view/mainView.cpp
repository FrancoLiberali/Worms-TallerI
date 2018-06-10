#include "mainView.h"
#include "newView/TextureManager.h"
#include <iostream>


mainView::mainView(EventHandler& eventHandler,  SdlScreen& screen)
		: screen(screen), eventHandler(eventHandler), open(true), stage(screen){
	this->init();

}

void mainView::init(){
	worm = new WormView(1);
	worm->setPlayerName("Pepito");
	worm->load(200, 400, &screen);

	//creamos el menu de armas
	menuWeapon = new MenuWeaponView;
	menuWeapon->buildWeapon();

	list<WeaponId> allowW;

	allowW.push_back(BAZOOKA);
	allowW.push_back(R_GRENADE);
	allowW.push_back(HOLY);
	allowW.push_back(G_GRENADE);
	allowW.push_back(DYNAMITE);
	allowW.push_back(AIRATTACK);
	allowW.push_back(BANANA);
	allowW.push_back(BATE);
	allowW.push_back(MORTERO);
	allowW.push_back(TELEPORT);
	menuWeapon->allowWeapon(allowW);
}

mainView::~mainView(){
	for (auto& it: worms){
		//delete it.second;
	}
	delete worm;
}

bool mainView::isOpen(){
	return open;
}

void mainView::close(){
	open = false;
}

void mainView::update(){
	screen.fill();
	//Escenario escenario(screen);
	stage.draw();
	while (!eventHandler.empty()){
		Event*  event = eventHandler.get();
		//this->procesar(mensaje);
		SDL_Delay(100);
		screen.fill();
		stage.draw();
		menuWeapon->draw(screen);

		event->process();
		delete event;
		worm->update();
		screen.render();
	}
	worm->update();
	menuWeapon->draw(screen);
	screen.render();
}

void mainView::procesar(std::string msg){
	std::cout << "procesar " << msg << std::endl;
}

WormView* mainView::getWormView(int id){
	std::cout << "ID-WORM" << id << std::endl;
	return worms[id];
}

void mainView::actionMenu(){
	menuWeapon->actionMenu();
}

bool mainView::hasClickedMenu(SDL_Point clickPoint){
	return this->menuWeapon->hasClickedMenu(clickPoint);
}

Weapon* mainView::retrieveWeaponClicked(SDL_Point clickPoint){
	return this->menuWeapon->retrieveWeaponClicked(clickPoint);
}

void mainView::addWorm(int id, std::string player, int x, int y, int dir, int angle){
	WormView* worm = new WormView(id);
	worm->setPlayerName(player);
	worm->setDirection(dir);
	worm->setAngle(angle);
	worm->load(x,y, &screen);
	this->worms.emplace(id, worm);
}

void mainView::addViga(int x, int y, int angle){
	stage.addViga(x, y, angle);
}

std::string mainView::changeTurn(std::string namePlayer){
	//mostrar algo para saber que es el turno del jugador
	std::cout<<"TURNO: "<<namePlayer<<std::endl;
}