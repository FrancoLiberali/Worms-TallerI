#include "projectile.h"
#include <cmath>
#include "ray_cast_all_callback.h"
#include <vector>
#include <utility>
#include <iostream>

#define NUM_RAYS 72
#define DRAG_CONSTANT 0.2
#define WIND_CONSTANT 5
#define PROJECTILE_ANGULAR_DAMPING 1
#define EXPLOTION_CONSTANT 1.0 / 100000.0
#define LEFT -1
#define NO_VERTICAL_WIND 0

Projectile::Projectile(b2World& world_entry, int number_e, float x, float y, int direction_e, float angle, float vel, 
	int damage_e, int radius_e, int type, std::vector<int>& to_remove_e, MultipleProxy& proxy_e) : 
			world(world_entry), number(number_e), direction(direction_e), damage(damage_e), 
			radius(radius_e), to_remove(to_remove_e), proxy(proxy_e), user_data(type, this){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.fixedRotation = false;
	bodyDef.position.Set(x, y);
	this->body = this->world.CreateBody(&bodyDef);
	this->body->SetUserData((void*)&this->user_data);
	this->body->SetTransform(this->body->GetPosition(), angle);
	this->body->SetAngularDamping(PROJECTILE_ANGULAR_DAMPING);
	
	b2Vec2 vel_vec;
	vel_vec.x = vel * cos(angle);
	vel_vec.y = vel * sin(angle);
	this->body->SetLinearVelocity(vel_vec);
}

Projectile::~Projectile(){
	this->world.DestroyBody(this->body);
}

void Projectile::exploit(){
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
			b2Vec2 distance_vec = it->second - center;
			float distance = distance_vec.Normalize();
			float damage_by_distance = this->damage * (1- (distance / this->radius));
			distance_vec.Normalize();
			b2Vec2 impulse_by_distance = (damage_by_distance / (NUM_RAYS)) * EXPLOTION_CONSTANT * distance_vec;
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

void Projectile::update(float wind){
	b2Vec2 position = this->GetPosition();
	float angle = this->GetAngle();
	this->proxy.sendProjectilePosition(this->number, position.x, position.y, (this->direction == LEFT)? angle - M_PI : angle);
}

void Projectile::setWindForce(float wind){
	this->body->ApplyForce(b2Vec2(wind * WIND_CONSTANT, NO_VERTICAL_WIND), this->body->GetPosition(), true);
}

void Projectile::setDragForce(float missile_widht){
	// forma de calcularlo sacada de http://www.iforce2d.net/b2dtut/sticky-projectiles
	b2Vec2 pointing_direction = this->body->GetWorldVector(b2Vec2(missile_widht,0));
	b2Vec2 flight_direction = this->body->GetLinearVelocity();
	float flight_speed = flight_direction.Normalize();//normalizes and returns length
	
	float dot = b2Dot(flight_direction, pointing_direction);
	float drag_force_magnitude = (1 - fabs(dot)) * flight_speed * flight_speed * DRAG_CONSTANT * this->body->GetMass();
  
	b2Vec2 missile_tail_position = this->body->GetWorldPoint(b2Vec2(-missile_widht, 0));
	this->body->ApplyForce(drag_force_magnitude * -flight_direction, missile_tail_position, true);
}

b2Vec2 Projectile::GetPosition(){ 
	return this->body->GetPosition();
}

float32 Projectile::GetAngle(){ 
	return this->body->GetAngle();
}
	

