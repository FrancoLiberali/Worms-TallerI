#include "contact_listener.h"

void ContactListener::BeginContact(b2Contact* contact){
	printf("empieza contacto\n");
	//check if body A was delimiter
	UserData* data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	if (data && data->indicator == 2){
		std::cout << "delimiter\n";
		//check if body B was gusano
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (other_data && other_data->indicator == 1){
			Gusano* gusano = static_cast<Gusano*>(other_data->pointer);
			gusano->destroy();
		//check if body B was projectile
		} else if (other_data && other_data->indicator == 0){
			Projectile* projectile = static_cast<Projectile*>(other_data->pointer);
			projectile->destroy();
		}
		return;
	}
	
	//check if body B was delimiter
	data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (data && data->indicator == 2){
		std::cout << "delimiter\n";
		//check if body A was gusano
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if (other_data && other_data->indicator == 1){
			Gusano* gusano = static_cast<Gusano*>(other_data->pointer);
			gusano->destroy();
		//check if body A was projectile
		} else if (other_data && other_data->indicator == 0){
			Projectile* projectile = static_cast<Projectile*>(other_data->pointer);
			projectile->destroy();
		}
		return;
	}
		
	//check if fixture A was the foot sensor
	b2Fixture* fixture = contact->GetFixtureA();
	void* fixture_user_data = fixture->GetUserData();
	if (fixture_user_data && *((int*)fixture_user_data) == 1){
		std::cout << "es pie\n";
		float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
		if (other_angle >= -0.78f && other_angle <= 0.78f){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->newContact(other_angle);
		}
	}
	//check if fixture A was the head sensor
	if (fixture_user_data && *((int*)fixture_user_data) == 2){
		UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
		Gusano* gusano = static_cast<Gusano*>(data->pointer);
		gusano->headContact();
	}
	//check if fixture B was the foot sensor
	fixture = contact->GetFixtureB();
	fixture_user_data = fixture->GetUserData();
    if (fixture_user_data && *((int*)fixture_user_data) == 1){
		std::cout << "es pie\n";
		float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
		if (other_angle >= -0.78f && other_angle <= 0.78f){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->newContact(other_angle);
		}
	}
	//check if fixture B was the head sensor
	if (fixture_user_data && *((int*)fixture_user_data) == 2){
		UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
		Gusano* gusano = static_cast<Gusano*>(data->pointer);
		gusano->headContact();
	}
		
	//check if body A was a projectile
	data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	if (data && data->indicator == 0){
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if ((other_data && other_data->indicator != 2) || (!other_data)){//viga no tiene data
			Projectile* projectile = static_cast<Projectile*>(data->pointer);
			projectile->exploit();
		}
	}
	//check if body B was a projectile
	data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (data && data->indicator == 0){
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if ((other_data && other_data->indicator != 2) || (!other_data)){//viga no tiene data
			Projectile* projectile = static_cast<Projectile*>(data->pointer);
			projectile->exploit();
		}
	}
}
		
void ContactListener::EndContact(b2Contact* contact){
	if (contact->GetFixtureA()->GetBody()->GetWorld()->IsLocked()){
		//check if fixture A was the foot sensor
		printf("termina contacto\n");
		b2Fixture* fixture = contact->GetFixtureA();
		void* fixture_user_data = fixture->GetUserData();
		if (fixture_user_data && *((int*)fixture_user_data) == 1){
			float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
			if (other_angle >= -0.78f && other_angle <= 0.78f){
				UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				gusano->finishContact(other_angle);
			}
		}
		//check if fixture A was the head sensor
		if (fixture_user_data && *((int*)fixture_user_data) == 2){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->headFinishContact();
		}
		//check if fixture B was the foot sensor
		fixture = contact->GetFixtureB();
		fixture_user_data = fixture->GetUserData();
		if (fixture_user_data && *((int*)fixture_user_data) == 1){
			float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
			if (other_angle >= -0.78f && other_angle <= 0.78f){
				UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				gusano->finishContact(other_angle);
			}
		}
		//check if fixture B was the head sensor
		if (fixture_user_data && *((int*)fixture_user_data) == 2){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->headFinishContact();
		}
	}
}
		
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	//check if body A was gusano
	UserData* data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	if (data && data->indicator == 1){
		Gusano* gusanoA = static_cast<Gusano*>(data->pointer);
		if (gusanoA->isInactive()){
			//check if body B was gusano or projectile
			UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
			if (other_data && (other_data->indicator == 1 || other_data->indicator == 0 || other_data->indicator == -1)){
				std::cout << "canceled\n";
				gusanoA->cancelMovement();
			}
		}
	}
	//check if body B was gusano
	data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (data && data->indicator == 1){
		Gusano* gusanoB = static_cast<Gusano*>(data->pointer);
		if (gusanoB->isInactive()){
			//check if body B was gusano or projectile
			UserData* other_data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
			if (other_data && (other_data->indicator == 1 || other_data->indicator == 0 || other_data->indicator == -1)){
				std::cout << "canceled\n";
				gusanoB->cancelMovement();
			}
		}
	}
}
