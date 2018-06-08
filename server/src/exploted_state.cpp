#include "exploted_state.h"
#include "moving_finished.h"

ExplotedState::ExplotedState(b2Body* body_entry) : body(body_entry){
}

ExplotedState::~ExplotedState(){
}

void ExplotedState::sumOneStep(){
	b2Vec2 vel = this->body->GetLinearVelocity();
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
