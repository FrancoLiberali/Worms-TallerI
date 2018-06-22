#include "projectile.h"
#include <cmath>
#include "ray_cast_all_callback.h"
#include <vector>
#include <utility>
#include <iostream>

#define NUM_RAYS 360

Projectile::Projectile(b2World& world_entry, int number_e, float x, float y, int direction, float angle, float vel, 
	int damage_e, int radius_e, int type, std::vector<int>& to_remove_e, MultipleProxy& proxy_e) : 
			world(world_entry), number(number_e), damage(damage_e), 
			radius(radius_e), to_remove(to_remove_e), proxy(proxy_e), user_data(type, this){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.position.Set(x, y);
	this->body = this->world.CreateBody(&bodyDef);
	this->body->SetUserData((void*)&this->user_data);
	this->body->SetTransform(this->body->GetPosition(), angle);
	
	b2Vec2 vel_vec;
	vel_vec.x = vel * cos(angle) * direction;
	vel_vec.y = vel * sin(angle);
	this->body->SetLinearVelocity(vel_vec);
}

Projectile::~Projectile(){
	this->world.DestroyBody(this->body);
}

void Projectile::exploit(){
	std::cout << "explosion\n";
	b2Vec2 center = this->body->GetPosition();
	float angle = this->GetAngle();
	this->proxy.sendProjectilePosition(this->number, center.x, center.y, angle);
	this->proxy.sendProjectileExplosion(this->number);
    for (int i = 0; i < NUM_RAYS; i++) {
		float pi = M_PI;
		float angle = (i / (float)NUM_RAYS) * 2 * pi;
        b2Vec2 ray_dir(cos(angle), sin(angle));
        b2Vec2 ray_end = center + this->radius * ray_dir;

        //check what this ray hits
        RayCastAllCallback callback;
        this->world.RayCast(&callback, center, ray_end);
        std::vector<std::pair<Gusano*, b2Vec2>> points = callback.getPoints();
        std::vector<std::pair<Gusano*, b2Vec2>>::iterator it = points.begin();
        for (; it != points.end(); ++it){
			std::cout << "hay algo\n";
			b2Vec2 distance_vec = it->second - center;
			float distance = distance_vec.Normalize();
			float damage_by_distance = this->damage * (1- (distance / this->radius));
			distance_vec.Normalize();
			b2Vec2 impulse_by_distance = (damage_by_distance / 100000 * (NUM_RAYS)) * distance_vec; //* (1/(float)NUM_RAYS);
			/*std::cout << center.x << "; " << center.y << "\n";
			std::cout << it->second.x << "; " << it->second.y << "\n";
			std::cout << angle << "\n";
			std::cout << distance << "\n";
			std::cout << damage_by_distance << "\n";
			std::cout << impulse_by_distance.x << "; " << impulse_by_distance.y << "\n";*/
			it->first->applyExplotion(it->second, damage_by_distance, impulse_by_distance);
		}
	}
	this->to_remove.push_back(this->number);
}

void Projectile::destroy(){
	b2Vec2 center = this->body->GetPosition();
	float angle = this->GetAngle();
	this->proxy.sendProjectilePosition(this->number, center.x, center.y, angle);
	this->proxy.sendProjectileExplosion(this->number);
	this->to_remove.push_back(this->number);
}

void Projectile::update(){
	b2Vec2 position = this->GetPosition();
	float angle = this->GetAngle();
	this->proxy.sendProjectilePosition(this->number, position.x, position.y, angle);
}

/* de cuando estaba intentado no necesitar ponerlos en el heap
 * Projectile::Projectile(Projectile&& other) : world(other.world), number(other.number), damage(other.damage), 
			radius(other.radius), to_remove(other.to_remove), proxy(other.proxy){
	std::cout << "se llama proyectil\n";
	this->body = other.body;
	other.body = nullptr;
	this->user_data = other.user_data;
	this->user_data->pointer = this;
	other.user_data = nullptr;
}*/
	
	

