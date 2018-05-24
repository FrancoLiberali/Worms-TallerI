#include "rotating_state.h"
#include "inactive_state.h"
#include "moving_finished.h"
#include <iostream>
#include <cmath>

RotatingState::RotatingState(b2Body* body_entry, b2Vec2 position, double desired_angle_entry): 
							body(body_entry), desired_angle(desired_angle_entry){
	double actual_angle = this->body->GetAngle();
	double new_x = position.x;
	double pi = M_PI;
	if (actual_angle < 0){
		new_x -= 0.5 * cos(pi/2 + actual_angle);
	} else {
		new_x += 0.5 * cos(pi/2 - actual_angle);
	}
	if (desired_angle < 0){
		new_x += 0.5 * cos(pi/2 + desired_angle);
	} else {
		new_x -= 0.5 * cos(pi/2 - desired_angle);
	}		
	double new_y = position.y - 0.5 * sin(pi/2 - actual_angle) + 0.5 * sin(pi/2 - desired_angle); //-0.04;
	this->new_position = new b2Vec2(new_x, new_y);
}

RotatingState::~RotatingState(){
	delete this->new_position;
}

void RotatingState::sumOneStep(){
	this->body->SetTransform(*(this->new_position), this->desired_angle);
	throw MovingFinished();
}

bool RotatingState::isInactive(){
	return false;
}

bool RotatingState::isFalling(){
	return false;
}
