#include "Box2D/Box2D.h"
#include "gusano.h"
#include "projectile.h"
#include "user_data.h"
#include <iostream>

#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

class ContactListener : public b2ContactListener{
	public:
		
		void BeginContact(b2Contact* contact){
			printf("empieza contacto\n");
			//check if body A was water
			UserData* data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
			if (data && data->indicator == 2){
				//check if body B was gusano
				UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
				if (other_data && other_data->indicator == 1){
					Gusano* gusano = static_cast<Gusano*>(other_data->pointer);
					gusano->sink();
				//check if body B was projectile
				} else if (other_data && other_data->indicator == 0){
					Projectile* projectile = static_cast<Projectile*>(data->pointer);
					projectile->sink();
				}
			}
			
			//check if body B was water
			data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
			if (data && data->indicator == 2){
				//check if body A was gusano
				UserData* other_data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
				if (other_data && other_data->indicator == 1){
					Gusano* gusano = static_cast<Gusano*>(other_data->pointer);
					gusano->sink();
				//check if body A was projectile
				} else if (other_data && other_data->indicator == 0){
					Projectile* projectile = static_cast<Projectile*>(data->pointer);
					projectile->sink();
				}
			}
				
			//check if fixture A was the foot sensor
			b2Fixture* fixture = contact->GetFixtureA();
			void* fixture_user_data = fixture->GetUserData();
			if (fixture_user_data){
				float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
				if (other_angle >= -0.78f && other_angle <= 0.78f){
					UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
					Gusano* gusano = static_cast<Gusano*>(data->pointer);
					gusano->newContact(other_angle);
				}
			}
            //check if fixture B was the foot sensor
            fixture = contact->GetFixtureB();
            fixture_user_data = fixture->GetUserData();
            if (fixture_user_data){
				float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
				if (other_angle >= -0.78f && other_angle <= 0.78f){
					UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
					Gusano* gusano = static_cast<Gusano*>(data->pointer);
					gusano->newContact(other_angle);
				}
			}
			//check if body A was a projectile
			data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
			if (data && data->indicator == 0){
				Projectile* projectile = static_cast<Projectile*>(data->pointer);
				projectile->exploit();
			}
			//check if body B was a projectile
			data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
			if (data && data->indicator == 0){
				Projectile* projectile = static_cast<Projectile*>(data->pointer);
				projectile->exploit();
			}
		}
		
		void EndContact(b2Contact* contact){
			if (contact->GetFixtureA()->GetBody()->GetWorld()->IsLocked()){
				//check if fixture A was the foot sensor
				printf("termina contacto\n");
				b2Fixture* fixture = contact->GetFixtureA();
				void* fixture_user_data = fixture->GetUserData();
				if (fixture_user_data){
					float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
					if (other_angle >= -0.78f && other_angle <= 0.78f){
						UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
						Gusano* gusano = static_cast<Gusano*>(data->pointer);
						gusano->finishContact(other_angle);
					}
				}
				//check if fixture B was the foot sensor
				fixture = contact->GetFixtureB();
				fixture_user_data = fixture->GetUserData();
				if (fixture_user_data){
					float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
					if (other_angle >= -0.78f && other_angle <= 0.78f){
						UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
						Gusano* gusano = static_cast<Gusano*>(data->pointer);
						gusano->finishContact(other_angle);
					}
				}
			}
		}
		
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
			//check if body A was gusano
			UserData* data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
			if (data && data->indicator == 1){
				//check if body B was gusano
				UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
				if (other_data && other_data->indicator == 1){
					Gusano* gusanoA = static_cast<Gusano*>(data->pointer);
					Gusano* gusanoB = static_cast<Gusano*>(other_data->pointer);
					if (gusanoA->isInactive()){
						std::cout << "canceled\n";
						gusanoA->cancelMovement();
					}
					if (gusanoB->isInactive()){
						std::cout << "canceled\n";
						gusanoB->cancelMovement();
					}
				}
			}
		}
};

#endif
