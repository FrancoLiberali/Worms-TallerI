#include "jumping_state.h"
#include "moving_finished.h"

JumpingState::JumpingState(){
}

JumpingState::~JumpingState(){
}

void JumpingState::sumOneStep(){
}

bool JumpingState::isInactive(){
	return false;
}

bool JumpingState::isFalling(){
	return true;
}
