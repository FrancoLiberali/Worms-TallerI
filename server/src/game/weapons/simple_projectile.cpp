#include "game/weapons/simple_projectile.h"

SimpleProjectile::SimpleProjectile(b2World& world_entry, int number, float x, float y, 
	int direction, float angle, float vel, int damage_e, int radius_e, std::vector<int>& to_remove, MultipleProxy& proxy)
		: Projectile(world_entry, number, x, y, direction, angle, vel, damage_e, radius_e, SIMPLE_TYPE, to_remove, proxy){
}

SimpleProjectile::~SimpleProjectile(){
}
