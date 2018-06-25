#include "game/weapons/banana.h"

#define LEFT -1
#define BANANA_ID 5
#define BANANA_DENSITY 1
#define BANANA_FRICTION 0.5
#define BANANA_RESTITUTION 1.0

Banana::Banana(b2World& world_entry, int number, float x, float y, int direction, float angle, float power, 
	GameConstants& info, std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time) : 
			RegresiveProjectile(world_entry, number, x, y, direction, 
			angle, info.banana_vel * power, info.banana_damage, 
			info.banana_radius, to_remove_e, proxy, time){
	b2Vec2 vertices[7];
	vertices[0].Set(0.05f, -0.15f);
	vertices[1].Set(0.05f, 0.15f);
	vertices[2].Set(0.0f, 0.1f);
	vertices[3].Set(-0.05f, 0.05f);
	vertices[4].Set(-0.1f, 0.0f);
	vertices[5].Set(-0.05f, -0.05f);
	vertices[6].Set(0.0f, -0.1f);
	
	int32 count = 7;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = BANANA_DENSITY;
	fixtureDef.friction = BANANA_FRICTION;
	fixtureDef.restitution = BANANA_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, BANANA_ID, direction, position.x, position.y, (this->direction == LEFT)? angle - M_PI : angle);
}

Banana::~Banana(){
}
