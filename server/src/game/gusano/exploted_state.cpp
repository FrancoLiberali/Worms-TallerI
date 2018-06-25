#include "game/gusano/exploted_state.h"
#include "moving_finished.h"

ExplotedState::ExplotedState(GusanoBody& body_e) : body(body_e){
}

ExplotedState::~ExplotedState(){
}

void ExplotedState::update(b2Vec2 position){
	b2Vec2 vel = this->body.getLinearVelocity();
	if (vel.x == 0 && vel.y == 0){
		throw MovingFinished();
	}
}

bool ExplotedState::isInactive(){
	return false;
}

bool ExplotedState::isFalling(){
	return false;
}

bool ExplotedState::isExploted(){
	return true;
}
