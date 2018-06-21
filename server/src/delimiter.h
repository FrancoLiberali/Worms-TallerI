#include "Box2D/Box2D.h"
#include "user_data.h"

#ifndef __DELIMITER_H__
#define __DELIMITER_H__
class Delimiter{
	private:
		UserData user_data;
	public:
		Delimiter(b2World& world, float x_from, float y_from, float x_to, float y_to);
		
		~Delimiter();		
};

#endif
