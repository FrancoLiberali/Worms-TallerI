#include "morter.h"

Morter::Morter(b2World& world_entry, int number, float x, float y, int direction, float angle, float power, 
	GameConstants& info, std::vector<int>& to_remove, std::vector<FragmentInfo>& to_create_e, MultipleProxy& proxy) : 
			FragmentProjectile(world_entry, number, x, 
			y, direction, angle, info.morter_vel * power, info.morter_damage, info.morter_radius, 
			to_remove, proxy, info.morter_fragment_damage,  info.morter_fragment_radius,  
			info.morter_cant_fragments, to_create_e){
	b2Vec2 vertices[6];
	vertices[0].Set(-0.2f, 0.15f);
	vertices[1].Set(-0.2f, -0.15f);
	vertices[2].Set(0.15f, -0.15f);
	vertices[3].Set(0.2f, -0.05f);
	vertices[4].Set(0.2f, 0.05f);
	vertices[5].Set(0.15f, 0.15f);
	
	int32 count = 6;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, 2, direction, position.x, position.y, (this->direction == -1)? angle - M_PI : angle);
}

Morter::~Morter(){
}

void Morter::update(float wind){
	this->setWindForce(wind);
	this->setDragForce(0.2);
	Projectile::update(wind);
}
