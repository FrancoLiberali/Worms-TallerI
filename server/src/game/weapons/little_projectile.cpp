#include "game/weapons/little_projectile.h"

#define LEFT -1
#define LITTLE_ID 11
#define LITTLE_DENSITY 1
#define LITTLE_FRICTION 0
#define LITTLE_RESTITUTION 0
#define LITTLE_RADIUS 0.05
#define LITTLE_GROUP -1

LittleProjectile::LittleProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, float vel, 
int damage, int radius, std::vector<int>& to_remove, MultipleProxy& proxy) : 
			SimpleProjectile(world_entry, number, x, y, direction, angle, vel, damage, radius, to_remove, proxy){
				
	b2CircleShape circleShape;
    circleShape.m_radius = LITTLE_RADIUS;
    
    b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = LITTLE_DENSITY;
	fixtureDef.friction = LITTLE_FRICTION;
	fixtureDef.restitution = LITTLE_RESTITUTION;
	
	fixtureDef.filter.groupIndex = LITTLE_GROUP;

	this->body->CreateFixture(&fixtureDef);
	this->body->SetFixedRotation(true);
	this->body->SetBullet(true);
	
	proxy.sendProjectileCreation(this->number, LITTLE_ID, direction, x, y, angle);
}

LittleProjectile::~LittleProjectile(){
}
