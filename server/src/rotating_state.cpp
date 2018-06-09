#include "rotating_state.h"
#include "inactive_state.h"
#include "rotating_finished.h"
#include <iostream>
#include <cmath>

RotatingState::RotatingState(b2Body* body_entry, b2Vec2 position, double desired_angle_entry): 
							body(body_entry), desired_angle(desired_angle_entry){
	double actual_angle = this->body->GetAngle();
	double new_x = position.x;
	double new_y = position.y;
	double pi = M_PI;
	//actual_angle = actual_angle % (2 * pi); ESTABA CON ESTOOOO
	//desired_angle = desired_angle % (2 * pi);
	if ((actual_angle < -pi/2 && actual_angle > -3*pi/2) || (actual_angle > pi/2 && actual_angle < 3*pi/2)){
		new_y += 0.5 * cos(actual_angle);
	} else {
		new_y -= 0.5 * cos(actual_angle);
	}
	new_x += 0.5 * sin (actual_angle);
	if ((desired_angle < -pi/2 && desired_angle > -3*pi/2) || (desired_angle > pi/2 && desired_angle < 3*pi/2)){
		new_y -= 0.5 * cos(desired_angle);
	} else {
		new_y += 0.5 * cos(desired_angle);
	}
	new_x -= 0.5 * sin (desired_angle);
	/*if (actual_angle < 0){
		new_x -= 0.5 * cos(pi/2 + actual_angle);
	} else if (actual_angle > 0){
		new_x += 0.5 * cos(pi/2 - actual_angle);
	}
	if (desired_angle < 0){
		new_x += 0.5 * cos(pi/2 + desired_angle);
	} else if (desired_angle > 0){
		new_x -= 0.5 * cos(pi/2 - desired_angle);
	}		
	double new_y = position.y - 0.5 * sin(pi/2 - actual_angle) + 0.5 * sin(pi/2 - desired_angle); //-0.04;*/
	//new_x += 0.5 * (sin(actual_angle) - sin(desired_angle));
	//new_y += 0.5 * (cos(desired_angle) - cos(actual_angle));
	b2Vec2 vec(new_x, new_y);
	this->new_position = vec;
}

RotatingState::~RotatingState(){
}

void RotatingState::sumOneStep(){
	this->body->SetTransform(this->new_position, this->desired_angle);
	throw RotatingFinished();
}

bool RotatingState::isInactive(){
	return false;
}

bool RotatingState::isFalling(){
	return false;
}
