#include "WormView.h"

WormView::WormView(){}

void WormView::load(int x, int y, Window* window){
	this->window = window;
	anime.load("wwalk.png", *window);
	anime.setPos(x, y);
	anime.setFrames(15);
	anime.render();
}

void WormView::update(){
	anime.render();
}
