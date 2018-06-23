#include "fragment_projectile.h"
#include "little_projectile.h"
#include <iostream>

FragmentProjectile::FragmentProjectile(b2World& world_entry, int number, float x, float y, int direction, float angle, 
float vel_e, int damage_e, int radius_e, std::vector<int>& to_remove_e, MultipleProxy& proxy, 
int fragment_damage_e, int fragment_radius_e, unsigned int cant_fragments_e, std::vector<FragmentInfo>& to_create_e)
		: Projectile(world_entry, number, x, y, direction, angle, vel_e, damage_e, radius_e, 0, to_remove_e, proxy), 
		fragment_damage(fragment_damage_e), fragment_radius(fragment_radius_e), 
		cant_fragments(cant_fragments_e), vel(vel_e), to_create(to_create_e){
}

FragmentProjectile::~FragmentProjectile(){
}

void FragmentProjectile::exploit(){
	Projectile::exploit();
	std::cout << "explosion fragmental\n";
	b2Vec2 center = this->body->GetPosition();
    for (int i = 0; i < cant_fragments; i++) {
		float pi = M_PI;
		float angle = (i / (float)cant_fragments) * 2 * pi;
		std::cout << angle << "\n";
		int direction = 0;
		if (angle < pi/2 || angle > 3 * pi / 2){
			direction = 1;
		} else {
			direction = -1;
		}
        
        this->to_create.push_back(std::move(FragmentInfo(center.x, center.y, direction,
				angle, this->vel, this->fragment_damage, this->fragment_radius)));
	}
}

/* de cuando estaba intentado no necesitar ponerlos en el heap
 * FragmentProjectile::FragmentProjectile(FragmentProjectile&& other) : Projectile(std::move(other)), fragment_damage(other.fragment_damage), 
		fragment_radius(other.fragment_radius),	cant_fragments(other.cant_fragments), vel(other.vel), to_create(other.to_create){
	std::cout << "se llama\n";
}*/
	
