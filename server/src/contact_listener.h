#include "Box2D/Box2D.h"
#include "gusano.h"

#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

class ContactListener : public b2ContactListener{
	private:
		bool continue_simulation = false;
	public:
		/*void EndContact(b2Contact* contact) {
			printf("end contact\n");
			b2Body* body1 = contact->GetFixtureA()->GetBody();
			b2Body* body2 = contact->GetFixtureB()->GetBody();
			void* body1UserData = body1->GetUserData();
			void* body2UserData = body2->GetUserData();
			if (body1UserData && body2UserData){
				printf("entro\n");
				int* data1 = static_cast<int*>(body1UserData);
				int* data2 = static_cast<int*>(body2UserData);
				printf("data 1: %i\n",*data1);
				printf("data 2: %i\n",*data2);
				if (((*data1) == 1 && (*data2) == 0) || ((*data1) == 0 & (*data2) == 1)){
					printf("cayendo\n");
					b2Vec2 vel = body1->GetLinearVelocity();
					vel.x = 0;
					body1->SetLinearVelocity( vel );
					body2->SetLinearVelocity( vel );
					this->continue_simulation = true;
				}
			}
		}
		
		bool should_continue(){
			return this->continue_simulation;
		}*/
		
		void BeginContact(b2Contact* contact){
			//check if fixture A was the foot sensor
			printf("empieza contacto\n");
			b2Fixture* fixture = contact->GetFixtureA();
			void* fixture_user_data = fixture->GetUserData();
			if (fixture_user_data){
				b2Body* other_body = contact->GetFixtureA()->GetBody();
				float other_angle = other_body->GetAngle();
				if (other_angle >= -0.78f && other_angle <= 0.78f){
					Gusano* gusano = static_cast<Gusano*>(fixture->GetBody()->GetUserData());
					gusano->newContact(other_angle);
				}
			}
            //check if fixture B was the foot sensor
            fixture = contact->GetFixtureB();
            fixture_user_data = fixture->GetUserData();
            if (fixture_user_data){
				b2Body* other_body = contact->GetFixtureA()->GetBody();
				float other_angle = other_body->GetAngle();
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
				Gusano* gusano = static_cast<Gusano*>(fixture->GetBody()->GetUserData());
				gusano->finishContact();
			}
            //check if fixture B was the foot sensor
            fixture = contact->GetFixtureB();
            fixture_user_data = fixture->GetUserData();
            if (fixture_user_data){
				Gusano* gusano = static_cast<Gusano*>(fixture->GetBody()->GetUserData());
				gusano->finishContact();
			}
		}		
};

#endif
