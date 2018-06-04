#include "Box2D/Box2D.h"
#include "user_data.h"

#ifndef __WATER_H__
#define __WATER_H__
class Water{
	private:
		UserData* user_data;
	public:
		Water(b2World& world, float x_from, float y_from, float x_to, float y_to);
		
		~Water();		
};

#endif
