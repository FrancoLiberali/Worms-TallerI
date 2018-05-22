#include "gusano_state.h"

#ifndef __JUMPING_STATE_H__
#define __JUMPING_STATE_H__

class JumpingState : public GusanoState{
	public:
		JumpingState();
		
		~JumpingState();
		
		virtual void sumOneStep();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
		
};

#endif
