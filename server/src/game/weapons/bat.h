#include "Box2D/Box2D.h"
#include "game/game_constants.h"
#include "game/gusano/gusano.h"

#ifndef __BAT_H__
#define __BAT_H__

class Bat{
	public:
		// Crea el efecto de un bateo realizado por el Gusano executer
		Bat(Gusano& executer, b2World& world, float x, float y, int direction, float angle, GameConstants& info);
		
		~Bat();
};

#endif
