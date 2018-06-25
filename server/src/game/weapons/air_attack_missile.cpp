#include "game/weapons/air_attack_missile.h"
#include <cmath>

#define RIGHT 1
#define AIR_ATTACK_ID 9
#define AIR_ATTACK_ANGLE -M_PI / 2
#define AIR_ATTACK_Y -2
#define AIR_ATTACK_DENSITY 1
#define AIR_ATTACK_FRICTION 0
#define AIR_ATTACK_RESTITUTION 0
#define AIR_ATTACK_WIDHT 0.5
#define AIR_ATTACK_HEIGHT 0.1

AirAttackMissile::AirAttackMissile(b2World& world_entry, int number, float x, GameConstants& info, 
		std::vector<int>& to_remove, MultipleProxy& proxy) : 
				SimpleProjectile(world_entry, number, x, AIR_ATTACK_Y, RIGHT, AIR_ATTACK_ANGLE, 
				info.air_attack_vel, info.air_attack_damage, info.air_attack_radius, to_remove, proxy){
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(AIR_ATTACK_WIDHT, AIR_ATTACK_HEIGHT);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = AIR_ATTACK_DENSITY;
	fixtureDef.friction = AIR_ATTACK_FRICTION;
	fixtureDef.restitution = AIR_ATTACK_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	proxy.sendProjectileCreation(this->number, AIR_ATTACK_ID, RIGHT, position.x, position.y, AIR_ATTACK_ANGLE);
}

AirAttackMissile::~AirAttackMissile(){
}

void AirAttackMissile::update(float wind){
	this->setWindForce(wind);
	this->setDragForce(AIR_ATTACK_WIDHT);
	Projectile::update(wind);
}
