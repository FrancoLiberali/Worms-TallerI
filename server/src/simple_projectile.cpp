#include "simple_projectile.h"

SimpleProjectile::SimpleProjectile(b2World& world_entry, int number, float x, float y, 
	int direction, float angle, float vel, int damage_e, int radius_e, std::map<int, Projectile*>& to_remove, MultipleProxy& proxy)
		: Projectile(world_entry, number, x, y, direction, angle, vel, damage_e, radius_e, 0, to_remove, proxy){
}

SimpleProjectile::~SimpleProjectile(){
}
