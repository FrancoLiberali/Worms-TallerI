#include "Box2D/Box2D.h"
#include <utility>
#include "game/gusano/gusano.h"
#include "game/Box2d_elements/user_data.h"
#include <iostream>

#ifndef __RAY_CAST_N_CALLBACK_H__
#define __RAY_CAST_N_CALLBACK_H__

class RayCastNearestCallback : public b2RayCastCallback{
	private:
		Gusano& executer;
		std::pair<Gusano*,b2Vec2> point_info;
	public:
		// Callback de la funcionalidad Raycast de BOX2D
		// Este callback sera llamado cuando se encuentre algun
		// cuerpo en el camino de una recta.
		RayCastNearestCallback(Gusano& gusano) : executer(gusano){}
		
		// Se encontro un cuerpo en el camino de una recta, 
		// si este es un gusano distinto del executer
		// se setea como el punto mas cercano desde el comienzo de la recta
		// y se devuelve buscar desde el inicio de la recta a este punto 
		// a ver si no hay otro mas cercano.
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			if (data && data->indicator == GUSANO_INDICATOR){
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				if (gusano != &this->executer){ 
					this->point_info.first = gusano;
					this->point_info.second = point;
				}
			}
			return fraction;
		}
		
		// Devuelve el gusano y el punto mas cercano hayado desde el comienzo de la recta.
		std::pair<Gusano*, b2Vec2> getPoint(){
			return this->point_info;
		}
};

#endif
