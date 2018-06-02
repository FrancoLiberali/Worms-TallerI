#include "Box2D/Box2D.h"
#include <iostream>
#include <stdio.h>
#include "gusano.h"
#include "viga.h"
#include "contact_listener.h"
#include "file.h"
#include "bazooka.h"
#include "morter.h"
#include <vector>
#include <algorithm>
#include "game_constants.h"
#include "little_projectile.h"

#define RIGHT 1
#define LEFT -1

int main(int argc, char** argv) {
	if (argc < 2){
		return 1;
	}
	
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);
	ContactListener contact_listener;
	world.SetContactListener(&contact_listener);
	
	Viga viga(world, 0.0f, 0.0f, 0.0f);
			
	Gusano gusano1(world, 3.5f, 0.52f, 0.0f);
	std::vector<Projectile*> to_remove;
	std::vector<LittleProjectile*> to_create;
	std::vector<Projectile*> in_simulation;
	GameConstants info;
	Projectile* bazooka = new Morter(world, 5.0f, 3.0f, -1.570796f, info, to_remove, to_create);
	in_simulation.push_back(bazooka);
	
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8; 
	int32 positionIterations = 3;
	
	//para activar los primeros empiezan contacto
	world.Step(timeStep, velocityIterations, positionIterations);
	world.Step(timeStep, velocityIterations, positionIterations);
	//5 seconds
	try{
		File file(argv[1], std::fstream::in);
		for (int32 i = 0; i < 300; ++i) {
			if (gusano1.isInactive()){
				char buff[1];
				*buff = '0';
				file.read(buff, 1);//en eof no da error, entonces si no recibe nada sigue
				switch (*buff){
					case 'a': printf("mover izquierda\n");
							  gusano1.move(LEFT);
							  break;
					case 'd': printf("mover derecha\n");
							  gusano1.move(RIGHT);
							  break;
					case 'q': printf("salto\n");
							  gusano1.jump();
							  break;
					case 'e': printf("vuelta\n");
							  gusano1.backJump();
							  break;
				}
			}
			world.Step(timeStep, velocityIterations, positionIterations);
			//process list for deletion
			std::vector<Projectile*>::iterator it = to_remove.begin();
			for (; it != to_remove.end(); ++it) {
				std::cout << "hay algo para destruir\n";
				Projectile* exploted_projectile = *it;
				//remove it from list of projectiles in simulation
				std::vector<Projectile*>::iterator it2 = std::find(in_simulation.begin(), in_simulation.end(), exploted_projectile);
				if (it2 != in_simulation.end()){
					in_simulation.erase(it2);
				}
				delete exploted_projectile;
			}
			to_remove.clear();
			std::vector<LittleProjectile*>::iterator it2 = to_create.begin();
			for (; it2 != to_create.end(); ++it2) {
				std::cout << "hay algo para crear\n";
				LittleProjectile* little = *it2;
				little->create();
				in_simulation.push_back((Projectile*)little);
			}
			to_create.clear();
			std::vector<Projectile*>::iterator it3 = in_simulation.begin();
			for (int i = 0; it3 != in_simulation.end(); ++it3, i++) {
				(*it3)->update();
				std::cout << "projectile " << i << ": " << (*it3)->GetPosition().x << "; " << (*it3)->GetPosition().y << "\n";
			}
				
			gusano1.sumOneStep();
			b2Vec2 position = gusano1.GetPosition();
			float32 angle = gusano1.GetAngle();
			
			printf("gusano1: %4.2f %4.2f %4.2f\n", position.x, 
			position.y, angle);

			//printf("gusano1: %4.2f %4.2f %4.2f ; proyectil: %4.2f %4.2f %4.2f \n", position.x, 
			//position.y, angle, position2.x, position2.y, angle2);
		}
	} catch (const std::exception& e){
		return 1;
	}
	return 0;
}
