#include "bazooka.h"

Bazooka::Bazooka(b2World& world_entry, float x, float y, float angle, GameConstants& info, std::vector<Projectile*>& to_remove) : 
			SimpleProjectile(world_entry, x ,y, angle, info.bazooka_vel, info.bazooka_damage, info.bazooka_radius, to_remove){
	b2Vec2 vertices[6];
	vertices[0].Set(-0.2f, 0.1f);
	vertices[1].Set(-0.2f, -0.1f);
	vertices[2].Set(0.0f, -0.1f);
	vertices[3].Set(0.05f, -0.05f);
	vertices[4].Set(0.05f, 0.05f);
	vertices[5].Set(0.0f, 0.1f);
	
	int32 count = 6;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
}

Bazooka::~Bazooka(){
}
