#include "Box2D/Box2D.h"

#ifndef __GUSANO_STATE_H__
#define __GUSANO_STATE_H__

class GusanoState{
	protected:
		int rest_steps;
		
	public:
		GusanoState(){}
		
		virtual ~GusanoState(){}
		
		virtual void sumOneStep() = 0;
		
		virtual bool isInactive() = 0;
		
		virtual bool isFalling() = 0;
		
		virtual bool isExploted(){return false;}
};

#endif
