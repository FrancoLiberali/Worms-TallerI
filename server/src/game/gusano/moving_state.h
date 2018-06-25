#include "game/gusano/gusano_state.h"

#ifndef __MOVING_STATE_H__
#define __MOVING_STATE_H__

class MovingState : public GusanoState{
	public:
		MovingState();
		
		~MovingState();
		
		// Actualiza la cantidad de frames que le quedan por caminar
		virtual void update(b2Vec2 position);
		
		// Devuelve false.
		virtual bool isInactive();
		
		// Devuelve false.
		virtual bool isFalling();
		
		// Reinicia la cantidad de frames que le quedan por caminar
		// para que el movimiento siga.
		virtual void move(GusanoState*& state, int new_dir, int& old_dir, 
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, GusanoBody& body);
};

#endif
