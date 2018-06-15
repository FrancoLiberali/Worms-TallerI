#include "mainView.h"
#include "newView/TextureManager.h"
#include <iostream>


mainView::mainView(EventHandler& eventHandler,  SdlScreen& screen)
		: screen(screen), eventHandler(eventHandler), open(true), stage(screen), endGame(false){
	this->init();
}

void mainView::init(){
	//creamos el menu de armas
	menuWeapon = new MenuWeaponView;
	menuWeapon->buildWeapon();

	list<WeaponId> allowW;
	//Armas permitidas
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
		delete it.second;
	}
}

bool mainView::isOpen(){
	return open;
}

void mainView::close(){
	open = false;
}

void mainView::update(){
	if (endGame)
		return;
	screen.fill();
	stage.draw();
	turnView.draw(screen.getRenderer(), 10 , 10);
	while (!eventHandler.empty()){
		Event*  event = eventHandler.get();
		screen.fill();
		stage.draw();
		turnView.draw(screen.getRenderer(), 10 , 10);
		menuWeapon->draw(screen);
		event->process();
		delete event;
		updateWorms();
		screen.render();
	}
	updateWorms();
	menuWeapon->draw(screen);
	screen.render();
}

WormView* mainView::getWormView(int id){
		return worms[id];
}

void mainView::updateWorms(){
	for(auto& it: this->worms)
		it.second->update();
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

void mainView::addWorm(int id, int idOwner, std::string player, int x, int y, int dir, int angle){
	WormView* worm = new WormView(id, idOwner, TextureManager().Instance().getCamera());
	worm->setPlayerName(player);
	worm->setDirection(dir);
	worm->setAngle(angle);
	worm->load(x,y, &screen);
	this->worms.emplace(id, worm);
}

void mainView::addViga(int x, int y, int angle){
	stage.addViga(x, y, angle);
}

std::string mainView::changeTurn(std::string namePlayer, int idWorm){
	turnView.setColor(255,10,255);
	SDL_Color red = {0,0,0};
	turnView.setText("Turno " + namePlayer,red);
	
	for(auto& it: this->worms)
		it.second->offFocus();
	worms[idWorm]->onFocus();
}

void mainView::showWinner(){
	//screen.clear();
	screen.fill();
	TextureManager::Instance().draw("win", 0 , 0, 0, screen.getRenderer());
	TextureManager::Instance().getCamera().focusCenterWindow();
	endGame = true;
	screen.render();
}

void mainView::showLosser(){
	//screen.clear();
	screen.fill();
	TextureManager::Instance().draw("lose", 0, 0, 0, screen.getRenderer());
	TextureManager::Instance().getCamera().focusCenterWindow();
	endGame = true;
	screen.render();
}

Camera& mainView::getCamera(){
	return TextureManager::Instance().getCamera();
}