#include "moving_state.h"
#include "moving_finished.h"

MovingState::MovingState(){
	this->rest_steps = 30;
}

MovingState::~MovingState(){
}

void MovingState::update(){
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

void MovingState::move(GusanoState*& state, int new_dir, int& old_dir, 
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, b2Body* body){
	//re-init the movement
	this->rest_steps = 30;
}
