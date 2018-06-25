#include "game/weapons/bat.h"
#include "game/Box2d_elements/ray_cast_nearest_callback.h"
#include <iostream>
#include <cmath>
#include <vector>

Bat::Bat(Gusano& executer, b2World& world, float x, float y, int direction, float angle, GameConstants& info){
	b2Vec2 center(x, y);
	b2Vec2 ray_dir(cos(angle) * direction, sin(angle));
    b2Vec2 ray_end = center + info.bat_max_radius * ray_dir;

    //check what this ray hits
    RayCastNearestCallback callback(executer);
    
    world.RayCast(&callback, center, ray_end);
    std::pair<Gusano*, b2Vec2> point = callback.getPoint();
    if (point.first){
		ray_dir.Normalize();
		point.first->applyExplotion(point.second, info.bat_damage, info.bat_impulse * ray_dir);
	}
}

Bat::~Bat(){
}
