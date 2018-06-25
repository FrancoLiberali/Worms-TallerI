#include "game/weapons/red_granade.h"
#include <iostream>
#include "game/weapons/fragment_info.h"

#define LEFT -1
#define RIGHT 1
#define RED_GRANADE_ID 4
#define RED_GRANADE_DENSITY 1
#define RED_GRANADE_FRICTION 1
#define RED_GRANADE_RESTITUTION 0.4

RedGranade::RedGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info_e, std::vector<int>& to_remove_e, std::vector<FragmentInfo>& to_create_e, 
		MultipleProxy& proxy, unsigned int time): 
			RegresiveProjectile(world_entry, number, x, y, direction, angle, 
			info_e.red_granade_vel * power, info_e.red_granade_damage, 
			info_e.red_granade_radius, to_remove_e, proxy, time), info(info_e), to_create(to_create_e){
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
	fixtureDef.density = RED_GRANADE_DENSITY;
	fixtureDef.friction = RED_GRANADE_FRICTION;
	fixtureDef.restitution = RED_GRANADE_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, RED_GRANADE_ID, direction, position.x, position.y, (this->direction == LEFT)? angle - M_PI : angle);
}

RedGranade::~RedGranade(){
}

void RedGranade::exploit(){
	Projectile::exploit();
	b2Vec2 center = this->body->GetPosition();
    for (int i = 0; i < this->info.red_granade_cant_fragments; i++) {
		float pi = M_PI;
		float angle = (i / (float) this->info.red_granade_cant_fragments) * 2 * pi;
		int direction = 0;
		if (angle < pi/2 || angle > 3 * pi / 2){
			direction = RIGHT;
		} else {
			direction = LEFT;
		}
        
        this->to_create.push_back(std::move(FragmentInfo(center.x, center.y, direction,
				angle, this->info.red_granade_vel, this->info.red_granade_fragment_damage, this->info.red_granade_fragment_radius)));
	}
}
