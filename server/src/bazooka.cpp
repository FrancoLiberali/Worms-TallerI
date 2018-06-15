#include "bazooka.h"
#include <cmath>

Bazooka::Bazooka(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info, std::map<int, Projectile*>& to_remove, MultipleProxy& proxy) : 
				SimpleProjectile(world_entry, number, x + (sqrt(0.3125) + 0.125) * cos(angle) * direction, 
				y + (sqrt(0.3125) + 0.125) * sin(angle), direction, angle, info.bazooka_vel * power, 
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
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	proxy.sendProjectileCreation(this->number, 1, direction, position.x, position.y, angle);
}

Bazooka::~Bazooka(){
}
