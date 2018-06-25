#include "Box2D/Box2D.h"
#include <vector>
#include <utility>
#include "game/gusano/gusano.h"
#include "game/Box2d_elements/user_data.h"
#include <iostream>

#ifndef __RAY_CAST_A_CALLBACK_H__
#define __RAY_CAST_A_CALLBACK_H__

#define GUSANO_INDICATOR 1
#define CONTINUE_SEARCHING 1

class RayCastAllCallback : public b2RayCastCallback{
	private:
		std::vector<std::pair<Gusano*,b2Vec2>> points;
	public:
		// Callback de la funcionalidad Raycast de BOX2D
		// Este callback sera llamado cuando se encuentre algun
		// cuerpo en el camino de una recta
		RayCastAllCallback(){}
		
		// Se encontro un cuerpo en el camino de una recta, 
		// si este es un gusano se agrega junto al punto que fue tocado
		// en la lista de puntos
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			if (data && data->indicator == GUSANO_INDICATOR){
				//es gusano
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				std::pair<Gusano*, b2Vec2> new_point(gusano, point);
				this->points.push_back(new_point);
			}
			return CONTINUE_SEARCHING;
		}
		
		// Devuelve la lista de gusanos y puntos hayados en el camino de la recta
		std::vector<std::pair<Gusano*, b2Vec2>> getPoints(){
			return this->points;
		}
};

#endif
