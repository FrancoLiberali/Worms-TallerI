#include "moving_state.h"
#include "moving_finished.h"

MovingState::MovingState(){
	this->rest_steps = 30;
}

MovingState::~MovingState(){
}

void MovingState::sumOneStep(){
	this->rest_steps -= 1;
	if (!this->rest_steps){
		throw MovingFinished();
	}
}

bool MovingState::isInactive(){
	return false;
}

bool MovingState::isFalling(){
	return false;
}
