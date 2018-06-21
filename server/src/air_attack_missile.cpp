#include "air_attack_missile.h"
#include <cmath>

AirAttackMissile::AirAttackMissile(b2World& world_entry, int number, float x, GameConstants& info, 
		std::vector<int>& to_remove, MultipleProxy& proxy) : 
				SimpleProjectile(world_entry, number, x, -2 , 1, -M_PI/2, 
				info.air_attack_vel, info.air_attack_damage, info.air_attack_radius, to_remove, proxy){
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5, 0.1);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	proxy.sendProjectileCreation(this->number, 9, 1, position.x, position.y, -M_PI/2);
}

AirAttackMissile::~AirAttackMissile(){
}
