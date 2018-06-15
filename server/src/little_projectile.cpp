#include "little_projectile.h"

LittleProjectile::LittleProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, float vel, 
int damage, int radius, std::map<int, Projectile*>& to_remove, MultipleProxy& proxy) : 
			SimpleProjectile(world_entry, number, x, y, direction, angle, vel, damage, radius, to_remove, proxy){
				
	b2CircleShape circleShape;
    circleShape.m_radius = 0.05; // very small
    
    b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 0.0f;
	
	//fixtureDef.filter.categoryBits = 0x1000;
	//fixtureDef.filter.maskBits = 0x0011;
	fixtureDef.filter.groupIndex = -1;

	this->body->CreateFixture(&fixtureDef);
	this->body->SetFixedRotation(true);
	this->body->SetBullet(true);
}

LittleProjectile::~LittleProjectile(){
}
