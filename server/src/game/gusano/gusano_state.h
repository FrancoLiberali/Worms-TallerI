#include "Box2D/Box2D.h"
#include "server/multiple_proxy.h"

#ifndef __GUSANO_STATE_H__
#define __GUSANO_STATE_H__

class GusanoState{
	protected:
		int rest_steps;
		
	public:
		GusanoState(){}
		
		virtual ~GusanoState(){}
		
		// Actualiza el estado de un Gusano al paso de un frame de simulacion
		virtual void update() = 0;
		
		// Devuelve si el estado es inactivo
		virtual bool isInactive() = 0;
		
		// Devuelve si el estado es cayendo
		virtual bool isFalling() = 0;
		
		// Devuelve si el estado es afectado por un explosion
		// Por defecto la respuesta es false.
		virtual bool isExploted(){return false;}
		
		// Mueve al Gusano, segun al estado en el que se encuentre.
		// Por defecto no hace nada.
		virtual void move(GusanoState*& state, int new_dir, int& old_dir, 
					int id, b2Vec2 position, float angle, MultipleProxy& proxy, b2Body* body){}
};

#endif
