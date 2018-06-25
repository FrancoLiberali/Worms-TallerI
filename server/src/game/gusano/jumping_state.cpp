#include "game/gusano/jumping_state.h"
#include "game/gusano/moving_finished.h"
#include <iostream>

#define MAX_HEIGHT_NO_DAMAGE 2
#define MAX_DAMAGE 25

JumpingState::JumpingState(Gusano* gusano_e) : gusano(gusano_e){
	this->y_max = this->gusano->GetPosition().y;
	this->y_last = this->gusano->GetPosition().y;
}

JumpingState::~JumpingState(){
	int diference = this->y_max - this->y_last - MAX_HEIGHT_NO_DAMAGE;
	if (diference > 0){
		if (diference > MAX_DAMAGE){
			diference = MAX_DAMAGE;
		}
		this->gusano->sufferDamage(diference);
	}
}

void JumpingState::update(b2Vec2 position){
	this->y_last = position.y;
	if (y_last > this->y_max){
		y_max = y_last;
	}
}

bool JumpingState::isInactive(){
	return false;
}

bool JumpingState::isFalling(){
	return true;
}
