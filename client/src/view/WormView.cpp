#include "WormView.h"
#include <iostream>

WormView::WormView(){
	this->state = STATIC;
	this->dir = 1;
}

void WormView::load(int x, int y, Window* window){
	this->setPos(x, y);
	this->window = window;
	//Cargamos todas las animaciones

	//animacion estática
	Animation* w_static = new Animation();
	w_static->load("wlazy.png", *window);
	//w_static->setPos(x,y);
	w_static->setFrames(33);
	this->animations.emplace(STATIC, w_static);

	//animacion de caminar
	Animation* w_walk = new Animation();
	w_walk->load("wwalk.png", *window);
	//w_walk->setPos(x,y);
	w_walk->setFrames(15);
	this->animations.emplace(MOVE, w_walk);

	//this->animations[state]->render();
	this->update();
}

void WormView::setPos(int x, int y){
		std::cout << "x: " << x << "y: " << y <<std::endl;
	this->x = x; this->y = y;
	/*for (auto& it : this->animations){
		it.second->setPos(x,y);
	}*/
}

void WormView::update(){
	std::cout << "Worm update" << std::endl;
	this->animations[state]->setPos(x,y);
	bool flip = (dir == 1)? true : false;
	this->animations[state]->render(flip, angle);
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

void WormView::setDirection(int dir){
	this->dir = dir;
}
void WormView::setAngle(int angle){
	this->angle = angle;
}