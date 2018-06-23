#include "dynamite.h"

Dynamite::Dynamite(b2World& world_entry, int number, float x, float y, int direction,
		GameConstants& info, std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time) : 
			RegresiveProjectile(world_entry, number, x, 
			y, direction, 0, 0, info.dynamite_damage, 
			info.dynamite_radius, to_remove_e, proxy, time){
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.05f, 0.15f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 2.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	proxy.sendProjectileCreation(this->number, 7, direction, position.x, position.y, 0);
}

Dynamite::~Dynamite(){
}
