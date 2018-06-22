#include "gusano_state.h"
#include "Box2D/Box2D.h"

#ifndef __ROTATING_STATE_H__
#define __ROTATING_STATE_H__

class RotatingState : public GusanoState{
	private:
		b2Body* body;
		float desired_angle;
		b2Vec2 new_position;
		
		//lleva a un angulo cualquiera al rango (-2pi, 2pi)
		float normalizate(float angle);
	public:
		RotatingState(b2Body* body_entry, b2Vec2 position, double desired_angle_entry);
		
		~RotatingState();
		
		virtual void sumOneStep();
		
		virtual bool isInactive();
		
		virtual bool isFalling();
		
};

#endif
