#include "rotating_state.h"
#include "rotation_finished.h"
#include <iostream>

RotatingState::RotatingState(b2Body* body_entry, float angle) : body(body_entry), desired_angle(angle){
}

RotatingState::~RotatingState(){
}

void RotatingState::sumOneStep(){
	float actual_angle = this->body->GetAngle();
	//this angles can be not extact
	if (actual_angle >= desired_angle - 0.01 && actual_angle <= desired_angle + 0.01){
		throw RotationFinished();
	}
}

bool RotatingState::isInactive(){
	return false;
}

bool RotatingState::isFalling(){
	return false;
}
