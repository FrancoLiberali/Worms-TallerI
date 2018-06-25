#include "game/gusano/gusano_state.h"
#include "Box2D/Box2D.h"
#include "game/gusano/gusano.h"

#ifndef __JUMPING_STATE_H__
#define __JUMPING_STATE_H__

class JumpingState : public GusanoState{
	private:
		Gusano* gusano;
		float y_max;
		float y_last;
		
	public:
		JumpingState(Gusano* gusano_e);
		
		// Mira la diferencia de alturas entre el ultimo punto del
		// salto y el mas alto,
		// y en base a eso decide si el Gusano debe sufrir danio.
		virtual ~JumpingState();
		
		// Actualiza el estado para saber cual fue el punto mas
		// alto en la trayectoria del salto
		virtual void update(b2Vec2 position);
		
		// Devuelve false.
		virtual bool isInactive();
		
		// Devuelve true.
		virtual bool isFalling();
		
};

#endif
