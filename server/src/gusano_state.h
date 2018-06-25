#include "Box2D/Box2D.h"
#include "multiple_proxy.h"

#ifndef __GUSANO_STATE_H__
#define __GUSANO_STATE_H__

class GusanoState{
	protected:
		int rest_steps;
		
	public:
		GusanoState(){}
		
		virtual ~GusanoState(){}
		
		virtual void update() = 0;
		
		virtual bool isInactive() = 0;
		
		virtual bool isFalling() = 0;
		
		virtual bool isExploted(){return false;}
		
		virtual void move(GusanoState*& state, int new_dir, int& old_dir, 
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, b2Body* body){}
};

#endif
