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
};

#endif
