#include "saint_granade.h"

SaintGranade::SaintGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
	GameConstants& info, std::map<int, Projectile*>& to_remove_e, MultipleProxy& proxy, unsigned int time) : 
			RegresiveProjectile(world_entry, number, x + (sqrt(0.3125) + 0.2) * cos(angle) * direction, 
			y + (sqrt(0.3125) + 0.2) * sin(angle), direction, angle, info.holy_granade_vel * power, info.holy_granade_damage, 
			info.holy_granade_radius, to_remove_e, proxy, time){
	b2Vec2 vertices[7];
	vertices[0].Set(0.0f, -0.3f);
	vertices[1].Set(0.2f, -0.1f);
	vertices[2].Set(0.2f, 0.1f);
	vertices[3].Set(0.05f, 0.2f);
	vertices[4].Set(-0.05f, 0.2f);
	vertices[5].Set(-0.2f, 0.1f);
	vertices[6].Set(-0.2f, -0.1f);
	
	int32 count = 7;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.2f;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	proxy.sendProjectileCreation(this->number, 6, direction, position.x, position.y, angle);
}

SaintGranade::~SaintGranade(){
}
