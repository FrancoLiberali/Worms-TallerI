#include "Box2D/Box2D.h"
#include "gusano.h"

#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

class ContactListener : public b2ContactListener{
	private:
		bool continue_simulation = false;
	public:
		
		void BeginContact(b2Contact* contact){
			//check if fixture A was the foot sensor
			printf("empieza contacto\n");
			b2Fixture* fixture = contact->GetFixtureA();
			void* fixture_user_data = fixture->GetUserData();
			if (fixture_user_data){
				float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
				if (other_angle >= -0.78f && other_angle <= 0.78f){
					Gusano* gusano = static_cast<Gusano*>(fixture->GetBody()->GetUserData());
					gusano->newContact(other_angle);
				}
			}
            //check if fixture B was the foot sensor
            fixture = contact->GetFixtureB();
            fixture_user_data = fixture->GetUserData();
            if (fixture_user_data){
				float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
				if (other_angle >= -0.78f && other_angle <= 0.78f){
					Gusano* gusano = static_cast<Gusano*>(fixture->GetBody()->GetUserData());
					gusano->newContact(other_angle);
				}
			}
		}
		
		void EndContact(b2Contact* contact){
			//check if fixture A was the foot sensor
			printf("termina contacto\n");
			b2Fixture* fixture = contact->GetFixtureA();
			void* fixture_user_data = fixture->GetUserData();
			if (fixture_user_data){
				float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
				if (other_angle >= -0.78f && other_angle <= 0.78f){
					Gusano* gusano = static_cast<Gusano*>(fixture->GetBody()->GetUserData());
					gusano->finishContact(other_angle);
				}
			}
            //check if fixture B was the foot sensor
            fixture = contact->GetFixtureB();
            fixture_user_data = fixture->GetUserData();
            if (fixture_user_data){
				float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
				if (other_angle >= -0.78f && other_angle <= 0.78f){
					Gusano* gusano = static_cast<Gusano*>(fixture->GetBody()->GetUserData());
					gusano->finishContact(other_angle);
				}
			}
		}		
};

#endif
