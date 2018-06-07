#include "regresive_projectile.h"

RegresiveProjectile::RegresiveProjectile(b2World& world_entry, int number, float x, float y, 
		float angle, float vel, int damage_e, int radius_e, 
		std::map<int, Projectile*>& to_remove_e, MultipleProxy& proxy, unsigned int time_e) :
		Projectile(world_entry, number, x, y, angle, vel, damage_e, radius_e, 1, to_remove_e, proxy), time(time_e){
}

RegresiveProjectile::~RegresiveProjectile(){
}

void RegresiveProjectile::update(){
	this->time -= 1;
	if (this->time == 0){
		this->exploit();
	}
}
