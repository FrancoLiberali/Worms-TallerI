#include "Box2D/Box2D.h"
#include "game_constants.h"
#include "gusano.h"

#ifndef __BAT_H__
#define __BAT_H__

class Bat{
	public:
		Bat(Gusano* executer, b2World& world, float x, float y, int direction, float angle, GameConstants& info);
		
		~Bat();
};

#endif
