#include "simple_projectile.h"

SimpleProjectile::SimpleProjectile(b2World& world_entry, float x, float y, float angle, float vel, int damage_e, int radius_e, std::vector<Projectile*>& to_remove)
		: Projectile(world_entry, x, y, angle, vel, damage_e, radius_e, 0, to_remove){
}

SimpleProjectile::SimpleProjectile(b2World& world_entry, int damage_e, int radius_e, std::vector<Projectile*>& to_remove):
		Projectile(world_entry, damage_e, radius_e, to_remove){
}	

SimpleProjectile::~SimpleProjectile(){
}

void SimpleProjectile::update(){
}

void SimpleProjectile::create(float x, float y, float angle, float vel){
	Projectile::create(x, y, angle, vel, 0);
}
