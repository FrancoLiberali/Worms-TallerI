#include "rotating_state.h"
#include "inactive_state.h"
#include "rotating_finished.h"
#include <iostream>
#include <cmath>

#define GUSANO_WIDTH 0.5
#define DOS_PI 2 * M_PI

RotatingState::RotatingState(b2Body* body_entry, b2Vec2 position, double desired_angle_entry): 
							body(body_entry), desired_angle(desired_angle_entry){
	double actual_angle = this->body->GetAngle();
	double new_x = position.x;
	double new_y = position.y;
	double pi = M_PI;
	actual_angle = this->normalizate(actual_angle);
	desired_angle = this->normalizate(desired_angle);
	// busco la posicion en la que debe quedar el centro del gusano
	// para que con el desired angle el contacto con el suelo quede en el mismo lugar
	
	// primero de busca cual es la posicion del contacto con el suelo actual
	if ((actual_angle < -pi/2 && actual_angle > -3*pi/2) || (actual_angle > pi/2 && actual_angle < 3*pi/2)){
		new_y += GUSANO_WIDTH * cos(actual_angle);
	} else {
		new_y -= GUSANO_WIDTH * cos(actual_angle);
	}
	new_x += GUSANO_WIDTH * sin (actual_angle);
	
	// se lleva esa posicion de contacto con el suelo a posicion del centro
	// con el calculo inverso pero con el angulo deseado
	if ((desired_angle < -pi/2 && desired_angle > -3*pi/2) || (desired_angle > pi/2 && desired_angle < 3*pi/2)){
		new_y -= GUSANO_WIDTH * cos(desired_angle);
	} else {
		new_y += GUSANO_WIDTH * cos(desired_angle);
	}
	new_x -= GUSANO_WIDTH * sin (desired_angle);
	
	this->new_position = b2Vec2(new_x, new_y);
}

RotatingState::~RotatingState(){
}

void RotatingState::update(){
	this->body->SetTransform(this->new_position, this->desired_angle);
	throw RotatingFinished();
}

bool RotatingState::isInactive(){
	return false;
}

bool RotatingState::isFalling(){
	return false;
}

float RotatingState::normalizate(float angle){
	double pi = M_PI;
	if (angle < 0){
		while(angle < -DOS_PI){
			angle += DOS_PI;
		}
	} else {
		while(angle > DOS_PI){
			angle -= DOS_PI;
		}
	}
	return angle;
}
