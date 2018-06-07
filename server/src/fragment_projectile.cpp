#include "fragment_projectile.h"
#include "little_projectile.h"
#include <iostream>

FragmentProjectile::FragmentProjectile(b2World& world_entry, int number, float x, float y, float angle, 
float vel_e, int damage_e, int radius_e, std::map<int, Projectile*>& to_remove_e, MultipleProxy& proxy, 
int fragment_damage_e, int fragment_radius_e, unsigned int cant_fragments_e, std::vector<FragmentInfo*>& to_create_e)
		: Projectile(world_entry, number, x, y, angle, vel_e, damage_e, radius_e, 0, to_remove_e, proxy), 
		fragment_damage(fragment_damage_e), fragment_radius(fragment_radius_e), 
		cant_fragments(cant_fragments_e), vel(vel_e), to_create(to_create_e){
}

FragmentProjectile::~FragmentProjectile(){
}

void FragmentProjectile::update(int weapon){
	Projectile::update(weapon);
}

void FragmentProjectile::exploit(){
	Projectile::exploit();
	b2Vec2 center = this->body->GetPosition();
    for (int i = 0; i < cant_fragments; i++) {
		float pi = M_PI;
		float angle = (i / (float)cant_fragments) * 2 * pi;
		std::cout << angle << "\n";
        
        this->to_create.push_back(new FragmentInfo(center.x, center.y, angle, this->vel, this->fragment_damage, this->fragment_radius));
	}
}
