#include "game/gusano/gusano_state.h"
#include "Box2D/Box2D.h"

#ifndef __EXPLOTED_STATE_2_H__
#define __EXPLOTED_STATE_2_H__

class ExplotedState : public GusanoState{
	private:
		GusanoBody& body;
	public:
		ExplotedState(GusanoBody& body_e);
		
		~ExplotedState();
		
		// Actualiza el estado para saber si el gusano ya 
		// se quedo quieto o todavia se encuentra afectado por la explosion.
		virtual void update(b2Vec2 position);
		
		// Devuelve false.
		virtual bool isInactive();
		
		// Devuelve false.
		virtual bool isFalling();
		
		// Devuelve true.
		virtual bool isExploted();
		
};

#endif
