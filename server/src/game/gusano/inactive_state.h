#include "game/gusano/gusano_state.h"

#ifndef __INACTIVE_STATE_H__
#define __INACTIVE_STATE_H__
class InactiveState : public GusanoState{
	public:
		InactiveState();
		
		virtual ~InactiveState();
		
		// No hace nada, el paso del tiempo no afecta al estado inactivo
		virtual void update(b2Vec2 position);
		
		// Devuelve true
		virtual bool isInactive();
		
		// Devuelve false
		virtual bool isFalling();
		
		// Comienza el movimiento de un gusano,
		// levando su estado a en movimiento.
		virtual void move(GusanoState*& state, int new_dir, int& old_dir, 
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, GusanoBody& body);
};

#endif
