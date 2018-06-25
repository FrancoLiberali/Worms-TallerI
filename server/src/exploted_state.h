#include "gusano_state.h"
#include "Box2D/Box2D.h"

#ifndef __EXPLOTED_STATE_2_H__
#define __EXPLOTED_STATE_2_H__

class ExplotedState : public GusanoState{
	private:
		b2Body* body;
	public:
		ExplotedState(b2Body* body_entry);
		
		~ExplotedState();
		
		virtual void update();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
		
		virtual bool isExploted();
		
};

#endif
