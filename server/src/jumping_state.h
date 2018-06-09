#include "gusano_state.h"
#include "Box2D/Box2D.h"
#include "gusano.h"

#ifndef __JUMPING_STATE_H__
#define __JUMPING_STATE_H__

class JumpingState : public GusanoState{
	private:
		float y_max;
		float y_last;
		b2Body* body;
		Gusano* gusano;
	public:
		JumpingState(b2Body* body, Gusano* gusano);
		
		virtual ~JumpingState();
		
		virtual void sumOneStep();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
		
};

#endif
