#include "game/Box2d_elements/contact_listener.h"
#include "game/delimiter.h"

#include "game/weapons/fragment_projectile.h"
#include "game/weapons/simple_projectile.h"
#include "game/weapons/regresive_projectile.h"

#define MAX_GUSANO_ANGLE 0.78 //45 grados

void ContactListener::BeginContact(b2Contact* contact){
	//check if body A was delimiter
	UserData* data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	if (data && data->indicator == DELIMITER_INDICATOR){
		//check if body B was gusano
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (other_data && other_data->indicator == GUSANO_INDICATOR){
			Gusano* gusano = static_cast<Gusano*>(other_data->pointer);
			gusano->destroy();
		//check if body B was not regresive projectile
		} else if (other_data && (other_data->indicator == FRAGMENT_TYPE || other_data->indicator == SIMPLE_TYPE)){
			Projectile* projectile = static_cast<Projectile*>(other_data->pointer);
			projectile->destroy();
		}
		return;
	}
	
	//check if body B was delimiter
	data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (data && data->indicator == DELIMITER_INDICATOR){
		//check if body A was gusano
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if (other_data && other_data->indicator == GUSANO_INDICATOR){
			Gusano* gusano = static_cast<Gusano*>(other_data->pointer);
			gusano->destroy();
		//check if body A was not regresive projectile
		} else if (other_data && (other_data->indicator == FRAGMENT_TYPE || other_data->indicator == SIMPLE_TYPE)){
			Projectile* projectile = static_cast<Projectile*>(other_data->pointer);
			projectile->destroy();
		}
		return;
	}
		
	//check if fixture A was the foot sensor
	b2Fixture* fixture = contact->GetFixtureA();
	void* fixture_user_data = fixture->GetUserData();
	if (fixture_user_data && *((int*)fixture_user_data) == FOOT_SENSOR_DATA){
		float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
		if (other_angle >= -MAX_GUSANO_ANGLE && other_angle <= MAX_GUSANO_ANGLE){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->newContact(other_angle);
		}
	}
	//check if fixture A was the head sensor
	if (fixture_user_data && *((int*)fixture_user_data) == HEAD_SENSOR_DATA){
		UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
		Gusano* gusano = static_cast<Gusano*>(data->pointer);
		gusano->headContact();
	}
	//check if fixture B was the foot sensor
	fixture = contact->GetFixtureB();
	fixture_user_data = fixture->GetUserData();
    if (fixture_user_data && *((int*)fixture_user_data) == FOOT_SENSOR_DATA){
		float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
		if (other_angle >= -MAX_GUSANO_ANGLE && other_angle <= MAX_GUSANO_ANGLE){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->newContact(other_angle);
		}
	}
	//check if fixture B was the head sensor
	if (fixture_user_data && *((int*)fixture_user_data) == HEAD_SENSOR_DATA){
		UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
		Gusano* gusano = static_cast<Gusano*>(data->pointer);
		gusano->headContact();
	}
		
	//check if body A was a projectile
	data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	if (data && (data->indicator == FRAGMENT_TYPE || data->indicator == SIMPLE_TYPE)){
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if ((other_data && other_data->indicator != DELIMITER_INDICATOR) || (!other_data)){//viga no tiene data
			Projectile* projectile = static_cast<Projectile*>(data->pointer);
			projectile->exploit();
		}
	}
	//check if body B was a projectile
	data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (data && (data->indicator == FRAGMENT_TYPE || data->indicator == SIMPLE_TYPE)){
		UserData* other_data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if ((other_data && other_data->indicator != DELIMITER_INDICATOR) || (!other_data)){//viga no tiene data
			Projectile* projectile = static_cast<Projectile*>(data->pointer);
			projectile->exploit();
		}
	}
}
		
void ContactListener::EndContact(b2Contact* contact){
	if (contact->GetFixtureA()->GetBody()->GetWorld()->IsLocked()){
		//check if fixture A was the foot sensor
		b2Fixture* fixture = contact->GetFixtureA();
		void* fixture_user_data = fixture->GetUserData();
		if (fixture_user_data && *((int*)fixture_user_data) == FOOT_SENSOR_DATA){
			float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
			if (other_angle >= -MAX_GUSANO_ANGLE && other_angle <= MAX_GUSANO_ANGLE){
				UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				gusano->finishContact(other_angle);
			}
		}
		//check if fixture A was the head sensor
		if (fixture_user_data && *((int*)fixture_user_data) == HEAD_SENSOR_DATA){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->headFinishContact();
		}
		//check if fixture B was the foot sensor
		fixture = contact->GetFixtureB();
		fixture_user_data = fixture->GetUserData();
		if (fixture_user_data && *((int*)fixture_user_data) == FOOT_SENSOR_DATA){
			float other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
			if (other_angle >= -MAX_GUSANO_ANGLE && other_angle <= MAX_GUSANO_ANGLE){
				UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
				Gusano* gusano = static_cast<Gusano*>(data->pointer);
				gusano->finishContact(other_angle);
			}
		}
		//check if fixture B was the head sensor
		if (fixture_user_data && *((int*)fixture_user_data) == HEAD_SENSOR_DATA){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			gusano->headFinishContact();
		}
	}
}
		
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	//check if body A was gusano
	UserData* data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	if (data && data->indicator == GUSANO_INDICATOR){
		Gusano* gusanoA = static_cast<Gusano*>(data->pointer);
		if (gusanoA->isInactive()){
			//check if body B was gusano or projectile
			UserData* other_data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
			if (other_data && (other_data->indicator == GUSANO_INDICATOR 
				|| other_data->indicator == FRAGMENT_TYPE || other_data->indicator == SIMPLE_TYPE
				|| other_data->indicator == REGRESIVE_TYPE)){
				gusanoA->cancelMovement();
			}
		}
	}
	//check if body B was gusano
	data = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (data && data->indicator == GUSANO_INDICATOR){
		Gusano* gusanoB = static_cast<Gusano*>(data->pointer);
		if (gusanoB->isInactive()){
			//check if body B was gusano or projectile
			UserData* other_data = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
			if (other_data && (other_data->indicator == GUSANO_INDICATOR 
				|| other_data->indicator == FRAGMENT_TYPE || other_data->indicator == SIMPLE_TYPE
				|| other_data->indicator == REGRESIVE_TYPE)){
				gusanoB->cancelMovement();
			}
		}
	}
}
