#include "red_granade.h"
#include <iostream>
#include "fragment_info.h"

RedGranade::RedGranade(b2World& world_entry, int number, float x, float y, int direction, float angle, float power,
		GameConstants& info_e, std::vector<int>& to_remove_e, std::vector<FragmentInfo*>& to_create_e, 
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
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.4f;

	this->body->CreateFixture(&fixtureDef);
	b2Vec2 position = this->body->GetPosition();
	angle = this->body->GetAngle();
	proxy.sendProjectileCreation(this->number, 4, direction, position.x, position.y, (this->direction == -1)? angle - M_PI : angle);
}

RedGranade::~RedGranade(){
}

void RedGranade::exploit(){
	Projectile::exploit();
	b2Vec2 center = this->body->GetPosition();
    for (int i = 0; i < this->info.red_granade_cant_fragments; i++) {
		float pi = M_PI;
		float angle = (i / (float) this->info.red_granade_cant_fragments) * 2 * pi;
		std::cout << angle << "\n";
		int direction = 0;
		if (angle < pi/2 || angle > 3 * pi / 2){
			direction = 1;
		} else {
			direction = -1;
		}
        
        this->to_create.push_back(new FragmentInfo(center.x, center.y, direction,
				angle, this->info.red_granade_vel, this->info.red_granade_fragment_damage, this->info.red_granade_fragment_radius));
	}
}
