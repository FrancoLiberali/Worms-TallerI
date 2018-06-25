#include "game/weapons/regresive_projectile.h"

RegresiveProjectile::RegresiveProjectile(b2World& world_entry, int number, float x, float y, 
		int direction, float angle, float vel, int damage_e, int radius_e, 
		std::vector<int>& to_remove_e, MultipleProxy& proxy, unsigned int time_e) :
		Projectile(world_entry, number, x, y, direction, angle, vel, damage_e, radius_e, REGRESIVE_TYPE, 
		to_remove_e, proxy), time(time_e){
}

RegresiveProjectile::~RegresiveProjectile(){
}

void RegresiveProjectile::update(float wind){
	Projectile::update(wind);
	this->time -= 1;
	if (this->time == 0){
		this->exploit();
	}
}
