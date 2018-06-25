#include "game/weapons/bazooka.h"
#include <cmath>

#define LEFT -1
#define BAZOOKA_ID 1
#define BAZOOKA_DENSITY 1
#define BAZOOKA_FRICTION 0
#define BAZOOKA_RESTITUTION 0
#define BAZOOKA_WIDTH 0.125

Bazooka::Bazooka(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info, std::vector<int>& to_remove, MultipleProxy& proxy) : 
				SimpleProjectile(world_entry, number, x, y, direction, angle, info.bazooka_vel * power, 
				info.bazooka_damage, info.bazooka_radius, to_remove, proxy){
	b2Vec2 vertices[6];
	vertices[0].Set(-0.125f, 0.1f);
	vertices[1].Set(-0.125f, -0.1f);
	vertices[2].Set(0.12f, -0.1f);
	vertices[3].Set(0.125f, -0.05f);
	vertices[4].Set(0.125f, 0.05f);
	vertices[5].Set(0.12f, 0.1f);
	int32 count = 6;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = BAZOOKA_DENSITY;
	fixtureDef.friction = BAZOOKA_FRICTION;
	fixtureDef.restitution = BAZOOKA_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, BAZOOKA_ID, direction, position.x, position.y, 
								(this->direction == LEFT)? angle - M_PI : angle);
}

Bazooka::~Bazooka(){
}

void Bazooka::update(float wind){
	this->setWindForce(wind);
	this->setDragForce(BAZOOKA_WIDTH);
	Projectile::update(wind);
}
