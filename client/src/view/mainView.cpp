#include "mainView.h"

#include "../manager/SoundManager.h"
#include <iostream>

mainView::mainView(EventHandler& eventHandler,  SdlScreen& screen, Camera& camera)
		: screen(screen), camera(camera), eventHandler(eventHandler), open(true), 
		stage(screen, camera), endGame(false), watch(screen){
	this->init();
}

void mainView::init(){
	//creamos el menu de armas
	menuWeapon = new MenuWeaponView(camera);
	menuWeapon->buildWeapon();

	std::list<WeaponId> allowW;
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
	//SoundManager::Instance().playMusic(BACKGROUND);
}

mainView::~mainView(){
	for (auto& it: worms){
		delete it.second;
	}
	for (auto& it: bullets){
		delete it.second;
	}
}

bool mainView::isOpen(){
	return open;
}

void mainView::close(){
	open = false;
	SoundManager::Instance().stopAllSounds();
	SDL_HideWindow(screen.getWindow());
}

void mainView::openWindow(){
	printf("se abrio la ventana\n");
	open = true;
}

void mainView::update(){
	if (endGame)
		return;
	screen.fill();
	stage.draw();
	while (!eventHandler.empty()){
		Event*  event = eventHandler.get();
		screen.fill();
		stage.draw();
		panelInfo.draw(screen.getRenderer());
		watch.draw();
		menuWeapon->draw(screen);
		event->process();
		delete event;
		updateItems();
		screen.render();
	}
	updateItems();
	panelInfo.draw(screen.getRenderer());
	watch.draw();
	menuWeapon->draw(screen);
	screen.render();
}

WormView* mainView::getWormView(int id){
	return worms[id];
}

BulletView* mainView::getBulletView(int id){
	return bullets[id];
}

void mainView::updateItems(){
	for (auto& it: this->worms)
		it.second->update();
	for (auto& it: this->bullets)
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
	WormView* worm = new WormView(id, idOwner, camera);
	worm->setPlayerName(player);
	worm->setDirection(dir);
	worm->setAngle(angle);
	worm->load(x,y, &screen);
	this->worms.emplace(id, worm);
}

void mainView::addViga(int x, int y, int angle){
	stage.addViga(x, y, angle);
}

void mainView::addMissile(int id, WeaponId idWeapon, int dir, int posx, int posy, int angle){
	BulletView* bullet = BulletFactory::createBulletView(idWeapon, id, dir, posx, posy,
		 angle, screen, camera);
	this->bullets[id] = bullet;
}


std::string mainView::changeTurn(std::string namePlayer, int idWorm){
	panelInfo.setTextTun("Turno: " + namePlayer);
	watch.start();
	for(auto& it: this->worms){
		it.second->offFocus();
		it.second->unselect();
	}
	worms[idWorm]->select();
	worms[idWorm]->onFocus();
}

void mainView::showLosser(std::string name){
	printf("Alguien perdio\n");
}

Camera& mainView::getCamera(){
	return camera;
}

void mainView::WormShoot(int idWorm){
	worms[idWorm]->useWeapon();
}

void mainView::createStage(int widht, int height){
	stage.setDimention(widht, height);
	camera.setDimentionMap(widht, height);
}

void mainView::setBackground(std::string name){
	stage.setBackground(name);
}
void mainView::weaponDone(WeaponId id){
	Weapon* weaponView  = menuWeapon->findWeaponById(id);
	weaponView->done();
}

void mainView::second(){
	watch.update(screen.getRenderer());
}



void mainView::windChanged(int speed){
	//turnView.setText("VIENTO : " + std::to_string(speed) + " km/h", red);
	panelInfo.setTextWind("Viento: " + std::to_string(speed) + " km/h");
}