#include "game/weapons/morter.h"

#define LEFT -1
#define MORTER_ID 2
#define MORTER_DENSITY 1
#define MORTER_FRICTION 0
#define MORTER_RESTITUTION 0
#define MORTER_WIDHT 0.2

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
	fixtureDef.density = MORTER_DENSITY;
	fixtureDef.friction = MORTER_FRICTION;
	fixtureDef.restitution = MORTER_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, MORTER_ID, direction, position.x, position.y, (this->direction == LEFT)? angle - M_PI : angle);
}

Morter::~Morter(){
}

void Morter::update(float wind){
	this->setWindForce(wind);
	this->setDragForce(MORTER_WIDHT);
	Projectile::update(wind);
}
