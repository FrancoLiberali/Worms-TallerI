#include "game/weapons/dynamite.h"

#define LEFT -1
#define DYNAMITE_ID 7
#define DYNAMITE_DENSITY 1
#define DYNAMITE_FRICTION 2.0
#define DYNAMITE_RESTITUTION 0
#define DYNAMITE_WIDTH 0.05
#define DYNAMITE_HEIGHT 0.15

Dynamite::Dynamite(b2World& world_entry, int number, float x, float y, int direction, float angle,
		GameConstants& info, std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time) : 
			RegresiveProjectile(world_entry, number, x, 
			y, direction, angle, 0, info.dynamite_damage, 
			info.dynamite_radius, to_remove_e, proxy, time){
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(DYNAMITE_WIDTH, DYNAMITE_HEIGHT);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = DYNAMITE_DENSITY;
	fixtureDef.friction = DYNAMITE_FRICTION;
	fixtureDef.restitution = DYNAMITE_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, DYNAMITE_ID, direction, position.x, position.y, 
								(this->direction == LEFT)? angle - M_PI : angle);
}

Dynamite::~Dynamite(){
}
