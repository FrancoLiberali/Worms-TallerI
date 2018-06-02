#include "regresive_projectile.h"

RegresiveProjectile::RegresiveProjectile(b2World& world_entry, float x, float y, 
		float angle, float vel, int damage_e, int radius_e, std::vector<Projectile*>& to_remove_e, unsigned int time_e) :
		Projectile(world_entry, x, y, angle, vel, damage_e, radius_e, 1, to_remove_e), time(time_e){
}

RegresiveProjectile::~RegresiveProjectile(){
}

void RegresiveProjectile::update(){
	this->time -= 1;
	if (this->time == 0){
		this->exploit();
	}
}
