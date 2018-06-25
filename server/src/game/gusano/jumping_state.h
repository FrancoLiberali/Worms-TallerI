#include "game/gusano/gusano_state.h"
#include "Box2D/Box2D.h"
#include "game/gusano/gusano.h"

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
		
		// Mira la diferencia de alturas entre el ultimo punto del
		// salto y el mas alto,
		// y en base a eso decide si el Gusano debe sufrir danio.
		virtual ~JumpingState();
		
		// Actualiza el estado para saber cual fue el punto mas
		// alto en la trayectoria del salto
		virtual void update();
		
		// Devuelve false.
		virtual bool isInactive();
		
		// Devuelve true.
		virtual bool isFalling();
		
};

#endif
