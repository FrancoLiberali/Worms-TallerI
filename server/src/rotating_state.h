#include "gusano_state.h"
#include "Box2D/Box2D.h"

#ifndef __ROTATING_STATE_H__
#define __ROTATING_STATE_H__

class RotatingState : public GusanoState{
	private:
		b2Body* body;
		float desired_angle;
	public:
		RotatingState(b2Body* body_entry, float angle);
		
		~RotatingState();
		
		virtual void sumOneStep();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
		
};

#endif
