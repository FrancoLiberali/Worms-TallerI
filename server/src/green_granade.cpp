#include "green_granade.h"

GreenGranade::GreenGranade(b2World& world_entry, float x, float y, float angle, GameConstants& info, std::vector<Projectile*>& to_remove_e) : 
			SimpleProjectile(world_entry, x ,y, angle, info.green_granade_vel, info.green_granade_damage, info.green_granade_radius, to_remove_e){
	b2Vec2 vertices[7];
	vertices[0].Set(0.0f, -0.2f);
	vertices[1].Set(0.15f, -0.1f);
	vertices[2].Set(0.15f, 0.1f);
	vertices[3].Set(0.05f, 0.15f);
	vertices[4].Set(-0.05f, 0.15f);
	vertices[5].Set(-0.15f, 0.1f);
	vertices[6].Set(-0.15f, -0.1f);
	
	int32 count = 7;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
}

GreenGranade::~GreenGranade(){
}
