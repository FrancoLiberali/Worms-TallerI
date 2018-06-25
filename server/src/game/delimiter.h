#include "Box2D/Box2D.h"
#include "game/Box2d_elements/user_data.h"

#ifndef __DELIMITER_H__
#define __DELIMITER_H__

#define DELIMITER_INDICATOR 2

class Delimiter{
	private:
		const UserData user_data;
		b2Body* body;
	public:
		// Crea el objeto Delimiter, objeto
		// que se encarga de marcar los limites del mapa,
		// tal que cuando algun otro objeto quiera salir del mismo
		// sera destruido
		Delimiter(b2World& world, float x_from, float y_from, float x_to, float y_to);
		
		~Delimiter();		
		
		Delimiter(Delimiter&& other);
};

#endif
