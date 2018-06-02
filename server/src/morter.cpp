#include "morter.h"

Morter::Morter(b2World& world_entry, float x, float y, float angle, GameConstants& info, std::vector<Projectile*>& to_remove, std::vector<LittleProjectile*>& to_create_e) : 
			FragmentProjectile(world_entry, x ,y, angle, info.morter_vel, info.morter_damage, info.morter_radius, 
			to_remove, info.morter_fragment_damage,  info.morter_fragment_radius,  info.morter_cant_fragments, to_create_e){
	b2Vec2 vertices[6];
	vertices[0].Set(-0.25f, 0.15f);
	vertices[1].Set(-0.25f, -0.15f);
	vertices[2].Set(0.0f, -0.15f);
	vertices[3].Set(0.05f, -0.05f);
	vertices[4].Set(0.05f, 0.05f);
	vertices[5].Set(0.0f, 0.15f);
	
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

Morter::~Morter(){
}
