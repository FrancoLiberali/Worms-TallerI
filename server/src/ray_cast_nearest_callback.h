#include "Box2D/Box2D.h"
#include <utility>
#include "gusano.h"
#include "user_data.h"
#include <iostream>
#include "gusano.h"

#ifndef __RAY_CAST_N_CALLBACK_H__
#define __RAY_CAST_N_CALLBACK_H__

class RayCastNearestCallback : public b2RayCastCallback{
	private:
		Gusano& executer;
		std::pair<Gusano*,b2Vec2> point_info;
	public:
		RayCastNearestCallback(Gusano& gusano) : executer(gusano){}

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			if (data && data->indicator == 1){
				std::cout << "gusano encontrado\n";
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				if (gusano != &this->executer){ //no estoy seguro de que vaya a funcionar bien
					std::cout << "no era yo\n";
					this->point_info.first = gusano;
					this->point_info.second = point;
				}
			}
			return fraction;
			//return 1;
		}
		
		std::pair<Gusano*, b2Vec2> getPoint(){
			return this->point_info;
		}
};

#endif
