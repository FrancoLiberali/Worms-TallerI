#include "inactive_state.h"

InactiveState::InactiveState(){
	this->rest_steps = 0;
}

InactiveState::~InactiveState(){
}

void InactiveState::sumOneStep(){
}

bool InactiveState::isInactive(){
	return true;
}

bool InactiveState::isFalling(){
	return false;
}
