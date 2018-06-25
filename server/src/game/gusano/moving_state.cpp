#include "game/gusano/moving_state.h"
#include "game/gusano/moving_finished.h"

#define MOVING_FRAMES 30

MovingState::MovingState(){
	this->rest_steps = MOVING_FRAMES;
}

MovingState::~MovingState(){
}

void MovingState::update(b2Vec2 position){
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
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, GusanoBody& body){
	//re-init the movement
	this->rest_steps = MOVING_FRAMES;
}
