#include "morter.h"

Morter::Morter(b2World& world_entry, int number, float x, float y, float angle, int power, 
	GameConstants& info, std::map<int, Projectile*>& to_remove, std::vector<FragmentInfo*>& to_create_e, MultipleProxy& proxy) : 
			FragmentProjectile(world_entry, number, x + (sqrt(0.3125) + 0.2) * cos(angle), y + (sqrt(0.3125) + 0.2) * sin(angle),
			angle, info.morter_vel * power, info.morter_damage, info.morter_radius, 
			to_remove, proxy, info.morter_fragment_damage,  info.morter_fragment_radius,  info.morter_cant_fragments, to_create_e){
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
}

Morter::~Morter(){
}

void Morter::update(int to_respect){
	FragmentProjectile::update(2);
}