#include "gusano_state.h"

#ifndef __MOVING_STATE_H__
#define __MOVING_STATE_H__

class MovingState : public GusanoState{
	public:
		MovingState();
		
		~MovingState();
		
		virtual void sumOneStep();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
};

#endif
