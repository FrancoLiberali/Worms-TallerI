#include "game/gusano/inactive_state.h"
#include "game/gusano/moving_state.h"

#define MOVING_STATE 1
#define GUSANO_VEL 0.2

InactiveState::InactiveState(){
	this->rest_steps = 0;
}

InactiveState::~InactiveState(){
}

void InactiveState::update(){
}

bool InactiveState::isInactive(){
	return true;
}

bool InactiveState::isFalling(){
	return false;
}

void InactiveState::move(GusanoState*& state, int new_dir, int& old_dir, int id, b2Vec2 position, 
											float angle, MultipleProxy& proxy, b2Body* body){
	if (old_dir != new_dir){
		// si no estaba mirando hacia esa direccion solo se gira
		old_dir = new_dir;
		proxy.sendGusanoPosition(id, position.x, position.y, new_dir, angle);
	} else {
		state = new MovingState();
		proxy.sendStateChange(id, MOVING_STATE);
		b2Vec2 vel;
		vel.x = GUSANO_VEL * old_dir * cos(angle);
		vel.y = GUSANO_VEL * old_dir * sin(angle);
		body->SetLinearVelocity(vel);
		delete this;
	}
}
