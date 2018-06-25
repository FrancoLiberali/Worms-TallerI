#include "game/gusano/gusano_state.h"
#include "Box2D/Box2D.h"

#ifndef __ROTATING_STATE_H__
#define __ROTATING_STATE_H__

class RotatingState : public GusanoState{
	private:
		GusanoBody& body;
		const float desired_angle;
		b2Vec2 new_position;
		
		//lleva de un angulo cualquiera a uno en el rango (-2pi, 2pi)
		float normalizate(float angle);
	public:
		// Crea un estado de rotacion que hace el gusano rote al desired_angle
		RotatingState(GusanoBody& body, b2Vec2 position, float desired_angle_e);
		
		~RotatingState();
		
		// Cuando se actualiza, el gusano no se encuentra en simulacion
		// por lo que se puede realizar la rotacion.
		virtual void update(b2Vec2 position);
		
		// retorna false
		virtual bool isInactive();
		
		// retorna false
		virtual bool isFalling();
		
};

#endif
