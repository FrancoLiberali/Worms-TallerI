#include "game/weapons/green_granade.h"

#define LEFT -1
#define GREEN_GRANADE_ID 3
#define GREEN_GRANADE_DENSITY 1
#define GREEN_GRANADE_FRICTION 1.0
#define GREEN_GRANADE_RESTITUTION 0.4

GreenGranade::GreenGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
	GameConstants& info, std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time) : 
			RegresiveProjectile(world_entry, number, x, y, direction, angle, info.green_granade_vel * power, info.green_granade_damage, 
			info.green_granade_radius, to_remove_e, proxy, time){
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
	fixtureDef.density = GREEN_GRANADE_DENSITY;
	fixtureDef.friction = GREEN_GRANADE_FRICTION;
	fixtureDef.restitution = GREEN_GRANADE_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, GREEN_GRANADE_ID, direction, position.x, position.y, (this->direction == LEFT)? angle - M_PI : angle);
}

GreenGranade::~GreenGranade(){
}
