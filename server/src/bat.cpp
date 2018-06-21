#include "bat.h"
#include "ray_cast_nearest_callback.h"
#include "ray_cast_all_callback.h"
#include <iostream>
#include <cmath>
#include <vector>

Bat::Bat(Gusano& executer, b2World& world, float x, float y, int direction, float angle, GameConstants& info){
	std::cout << direction << "\n";
	b2Vec2 center(x, y);
	b2Vec2 ray_dir(cos(angle) * direction, sin(angle));
	std::cout << "ray dir: " << ray_dir.x << "; " << ray_dir.y << "\n";
	
    b2Vec2 ray_end = center + info.bat_max_radius * ray_dir;
    std::cout << "center: " << center.x << "; " << center.y << "\n";
    std::cout << "ray end: " << ray_end.x << "; " << ray_end.y << "\n";

    //check what this ray hits
    RayCastNearestCallback callback(executer); //mirar si es necesario executor
    
    world.RayCast(&callback, center, ray_end);
    std::pair<Gusano*, b2Vec2> point = callback.getPoint();
    if (point.first){
		std::cout << "hay algo\n";
		ray_dir.Normalize();
		std::cout << "apply point: " << point.second.x << "; " << point.second.y << "\n";
		std::cout << "gusano position: " << point.first->GetPosition().x << "; " << point.first->GetPosition().y << "\n";
		point.first->applyExplotion(point.second, info.bat_damage, info.bat_impulse * ray_dir);
	}
}

Bat::~Bat(){
}
