#include "gusano_state.h"

#ifndef __MOVING_STATE_H__
#define __MOVING_STATE_H__

class MovingState : public GusanoState{
	public:
		MovingState();
		
		~MovingState();
		
		virtual void update();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
		
		virtual void move(GusanoState*& state, int new_dir, int& old_dir, 
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, b2Body* body);
};

#endif
