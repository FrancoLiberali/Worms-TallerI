#include "game/Box2d_elements/contact_listener.h"
#include "game/delimiter.h"

#include "game/weapons/fragment_projectile.h"
#include "game/weapons/simple_projectile.h"
#include "game/weapons/regresive_projectile.h"

#define MAX_GUSANO_ANGLE 0.78 //45 grados
#define BEGIN 1
#define FINISH 0

void ContactListener::BeginContact(b2Contact* contact){
	UserData* dataA = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	UserData* dataB = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	//check if body A was delimiter
	this->checkDelimiter(dataA, dataB);
	//check if body B was delimiter
	this->checkDelimiter(dataB, dataA);
	
	b2Fixture* fixture = contact->GetFixtureA();
	void* fixture_user_data = fixture->GetUserData();
	float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
	//check if fixture A was the foot sensor
	this->checkFootSensor(fixture, fixture_user_data, other_angle, BEGIN);
	//check if fixture A was the head sensor
	this->checkHeadSensor(fixture, fixture_user_data, BEGIN);
	
	fixture = contact->GetFixtureB();
	fixture_user_data = fixture->GetUserData();
	other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
	//check if fixture B was the foot sensor
	this->checkFootSensor(fixture, fixture_user_data, other_angle, BEGIN);
	//check if fixture B was the head sensor
	this->checkHeadSensor(fixture, fixture_user_data, BEGIN);
		
	//check if body A was a projectile
	this->checkProjectile(dataA, dataB);
	//check if body B was a projectile
	this->checkProjectile(dataB, dataA);
}

void ContactListener::checkDelimiter(UserData* dataA, UserData* dataB){
	if (dataA && dataA->indicator == DELIMITER_INDICATOR){
		//check if body B was gusano
		if (dataB && dataB->indicator == GUSANO_INDICATOR){
			Gusano* gusano = static_cast<Gusano*>(dataB->pointer);
			gusano->destroy();
		//check if body B was not regresive projectile
		} else if (dataB && (dataB->indicator == FRAGMENT_TYPE || dataB->indicator == SIMPLE_TYPE)){
			Projectile* projectile = static_cast<Projectile*>(dataB->pointer);
			projectile->destroy();
		}
	}
}

void ContactListener::checkFootSensor(b2Fixture* fixture, void* fixture_data, float other_angle, int type){
	if (fixture_data && *((int*)fixture_data) == FOOT_SENSOR_DATA){
		if (other_angle >= -MAX_GUSANO_ANGLE && other_angle <= MAX_GUSANO_ANGLE){
			UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
			Gusano* gusano = static_cast<Gusano*>(data->pointer);
			if (type == BEGIN){
				gusano->newContact(other_angle);
			} else {
				gusano->finishContact(other_angle);
			}
		}
	}
}

void ContactListener::checkHeadSensor(b2Fixture* fixture, void* fixture_data, int type){
	if (fixture_data && *((int*)fixture_data) == HEAD_SENSOR_DATA){
		UserData* data = static_cast<UserData*>(fixture->GetBody()->GetUserData());
		Gusano* gusano = static_cast<Gusano*>(data->pointer);
		if (type == BEGIN){
			gusano->headContact();
		} else {
			gusano->headFinishContact();
		}
	}
}

void ContactListener::checkProjectile(UserData* dataA, UserData* dataB){
	if (dataA && (dataA->indicator == FRAGMENT_TYPE || dataA->indicator == SIMPLE_TYPE)){
		if ((dataB && dataB->indicator != DELIMITER_INDICATOR) || (!dataB)){//viga no tiene data
			Projectile* projectile = static_cast<Projectile*>(dataA->pointer);
			projectile->exploit();
		}
	}
}
		
void ContactListener::EndContact(b2Contact* contact){
	if (contact->GetFixtureA()->GetBody()->GetWorld()->IsLocked()){
		b2Fixture* fixture = contact->GetFixtureA();
		void* fixture_user_data = fixture->GetUserData();
		float other_angle = contact->GetFixtureB()->GetBody()->GetAngle();
		//check if fixture A was the foot sensor
		this->checkFootSensor(fixture, fixture_user_data, other_angle, FINISH);
		//check if fixture A was the head sensor
		this->checkHeadSensor(fixture, fixture_user_data, FINISH);
	
		fixture = contact->GetFixtureB();
		fixture_user_data = fixture->GetUserData();
		other_angle = contact->GetFixtureA()->GetBody()->GetAngle();
		//check if fixture B was the foot sensor
		this->checkFootSensor(fixture, fixture_user_data, other_angle, FINISH);
		//check if fixture B was the head sensor
		this->checkHeadSensor(fixture, fixture_user_data, FINISH);
	}
}
		
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	UserData* dataA = static_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	UserData* dataB = static_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData());
	//check if body A was gusano
	this->checkGusano(dataA, dataB);
	//check if body B was gusano
	this->checkGusano(dataB, dataA);
}

void ContactListener::checkGusano(UserData* dataA, UserData* dataB){
	if (dataA && dataA->indicator == GUSANO_INDICATOR){
		Gusano* gusanoA = static_cast<Gusano*>(dataA->pointer);
		if (gusanoA->isInactive()){
			//check if body B was gusano or projectile
			if (dataB && (dataB->indicator == GUSANO_INDICATOR 
				|| dataB->indicator == FRAGMENT_TYPE || dataB->indicator == SIMPLE_TYPE
				|| dataB->indicator == REGRESIVE_TYPE)){
				gusanoA->cancelMovement();
			}
		}
	}
}
