#include "Box2D/Box2D.h"
#include <iostream>
#include <stdio.h>
#include "gusano.h"
#include "viga.h"
#include "contact_listener.h"
#include "file.h"

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
	
	Viga viga(world, 0.0f, 0.0f, 0.2f);
			Viga viga2(world, 5.88f, 1.19f, 0.6f);
			
			Gusano gusano1(world, 5.5f, 2.0f, 0.2f);
	
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
			gusano1.sumOneStep();
			b2Vec2 position = gusano1.GetPosition();
			float32 angle = gusano1.GetAngle();
			//b2Vec2 position2 = gusano2.GetPosition();
			//float32 angle2 = gusano2.GetAngle();
			
			printf("gusano1: %4.2f %4.2f %4.2f\n", position.x, 
			position.y, angle);

			//printf("gusano1: %4.2f %4.2f %4.2f ; gusano2: %4.2f %4.2f %4.2f \n", position.x, 
			//position.y, angle, position2.x, position2.y, angle2);
		}
	} catch (const std::exception& e){
		return 1;
	}
	return 0;
}
