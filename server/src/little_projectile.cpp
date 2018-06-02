#include "little_projectile.h"

LittleProjectile::LittleProjectile(b2World& world_entry, float x_e, float y_e, float angle_e, float vel_e, int damage, int radius, std::vector<Projectile*>& to_remove) : 
			SimpleProjectile(world_entry, damage, radius, to_remove), x(x_e), y(y_e), angle(angle_e), vel(vel_e){
}

LittleProjectile::~LittleProjectile(){
}

void LittleProjectile::create(){
	SimpleProjectile::create(this->x , this->y, this->angle, this->vel);
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
