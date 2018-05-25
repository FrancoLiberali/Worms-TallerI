#include "Box2D/Box2D.h"
#include <vector>
#include <utility>
#include "gusano.h"
#include "user_data.h"

#ifndef __RAY_CAST_CALLBACK_H__
#define __RAY_CAST_CALLBACK_H__

class RayCastAllCallback : public b2RayCastCallback{
	private:
		std::vector<std::pair<Gusano*,b2Vec2>> points;
	public:
		RayCastAllCallback(){}

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction){
			void* fixture_user_data = fixture->GetUserData();
			//es gusano
			if (fixture_user_data){
				UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				std::pair<Gusano*, b2Vec2> new_point(gusano, point);
				this->points.push_back(new_point);
			}
			return 1;
		}
		
		std::vector<std::pair<Gusano*, b2Vec2>> getPoints(){
			return this->points;
			//retornar fraction en caso de no dunamic y guardar eso y despues mirar aca los que tengan menor que ese numero
		}
};

#endif
