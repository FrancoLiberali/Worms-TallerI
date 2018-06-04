#include "WormView.h"
#include <iostream>

WormView::WormView(){
	this->state = STATIC;
}

void WormView::load(int x, int y, Window* window){
	this->window = window;
	//Cargamos todas las animaciones

	//animacion estática
	Animation* w_static = new Animation();
	w_static->load("wlazy.png", *window);
	w_static->setPos(x,y);
	w_static->setFrames(33);
	this->animations.emplace(STATIC, w_static);

	//animacion de caminar
	Animation* w_walk = new Animation();
	w_walk->load("wwalk.png", *window);
	w_walk->setPos(x,y);
	w_walk->setFrames(15);
	this->animations.emplace(MOVE, w_walk);

	//this->animations[state]->render();
	this->update();
}

void WormView::setPos(int x, int y){
	this->x = x; this->y = y;
	/*for (auto& it : this->animations){
		it.second->setPos(x,y);
	}*/
}

void WormView::update(){
	//std::cout << "Worm update";
	this->animations[state]->setPos(x,y);
	this->animations[state]->render();
}

WormView::~WormView(){
	for (auto& it : this->animations){
		delete it.second;
	}
}

void WormView::changeState(WormState newState){
	if (this->state == newState)
		return;
	this->state = newState;
}
