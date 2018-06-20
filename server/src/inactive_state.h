#include "gusano_state.h"

#ifndef __INACTIVE_STATE_H__
#define __INACTIVE_STATE_H__
class InactiveState : public GusanoState{
	public:
		InactiveState();
		
		virtual ~InactiveState();
		
		virtual void sumOneStep();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
		
		virtual void move(GusanoState*& state, int new_dir, int& old_dir, 
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, b2Body* body);
};

#endif
