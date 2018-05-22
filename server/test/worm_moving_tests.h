#include <cxxtest/TestSuite.h>
#include <iostream>
#include "gusano.h"
#include "viga.h"
#include "contact_listener.h"
#include "Box2D/Box2D.h"
#include <cmath>

#define RIGHT 1
#define LEFT -1

class WormMovingTest : public CxxTest::TestSuite {
	public:
		float32 timeStep;
		int32 velocityIterations;
		int32 positionIterations;
		
		void setUp(){
			timeStep = 1.0f / 60.0f;
			velocityIterations = 8; 
			positionIterations = 3;
		}
		
		void test_not_inactive_after_move(){
			std::cout << "\nStarting no inactive test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.0f);
			Gusano gusano(world, 0.0f, 0.52f, 0.0f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			gusano.move(RIGHT);
			world.Step(timeStep, velocityIterations, positionIterations);
			TS_ASSERT(!gusano.isInactive());
			std::cout << "No inactive test pass";
		}
		
		void test_first_move_to_the_opposite_side_inactive(){
			std::cout << "\nStarting first move to the opposite side inactive test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.0f);
			Gusano gusano(world, 0.0f, 0.51f, 0.0f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			gusano.move(LEFT);
			world.Step(timeStep, velocityIterations, positionIterations);
			TS_ASSERT(gusano.isInactive());
			gusano.move(RIGHT);
			world.Step(timeStep, velocityIterations, positionIterations);
			TS_ASSERT(gusano.isInactive());
			std::cout << "First move to the opposite side inactive test pass";
		}
			
		void test_one_step(void){
			std::cout << "\nStarting one step test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.0f);
			Gusano gusano(world, 0.0f, 0.52f, 0.0f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			b2Vec2 position1 = gusano.GetPosition();
			float32 angle1 = gusano.GetAngle();
			
			gusano.move(RIGHT);
			
			while(!gusano.isInactive()){
				world.Step(timeStep, velocityIterations, positionIterations);
				gusano.sumOneStep();
			}
			
			b2Vec2 position2 = gusano.GetPosition();
			float32 angle2 = gusano.GetAngle();
			TS_ASSERT_EQUALS(angle1, angle2);
			float delta =  position2.x - position1.x;
			TS_ASSERT(delta < 0.101f);
			TS_ASSERT(delta > 0.098f); //the position of box2D can be not exact
			TS_ASSERT_EQUALS(position2.y, position1.y);
		
			std::cout << "One step test pass";
		}
		
		void test_velocity(void){
			std::cout << "\nStarting velocity test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.0f);
			Gusano gusano(world, 0.0f, 0.52f, 0.0f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			b2Vec2 position1 = gusano.GetPosition();
			float32 angle1 = gusano.GetAngle();
			
			gusano.move(RIGHT);
			int steps = 0;
			while(!gusano.isInactive()){
				world.Step(timeStep, velocityIterations, positionIterations);
				gusano.sumOneStep();
				steps += 1;
			}
			
			b2Vec2 position2 = gusano.GetPosition();
			float32 angle2 = gusano.GetAngle();
			TS_ASSERT_EQUALS(angle1, angle2);
			float delta =  position2.x - position1.x;
			float vel = delta / (steps * timeStep);
			TS_ASSERT(vel < 0.201f);
			TS_ASSERT(vel > 0.198f); //the position of box2D can be not exact
		
			std::cout << "Velocity test pass";
		}
		
		void test_until_45_degress_not_fall(void){
			std::cout << "\nStarting dont fall test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.78f); //45 degress
			Gusano gusano(world, 2.0f, 2.71f, 0.78f);
			
			Viga viga2(world, 10.0f, 0.0f, -0.78f); //-45 degress
			Gusano gusano2(world, 12.0f, -1.27f, -0.78f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			b2Vec2 position11 = gusano.GetPosition();
			b2Vec2 position21 = gusano2.GetPosition();
			for (int i = 0; i < 20; i++){
				//give some time to see if fall
				world.Step(timeStep, velocityIterations, positionIterations);
			}
			
			b2Vec2 position12 = gusano.GetPosition();
			b2Vec2 position22 = gusano2.GetPosition();
			float delta1x = position12.x - position11.x;
			float delta1y = position12.y - position11.y;
			float delta2x = position22.x - position21.x;
			float delta2y = position22.y - position21.y;
			TS_ASSERT(delta1x < 0.001);
			TS_ASSERT(delta1x > -0.001);
			TS_ASSERT(delta1y < 0.001);
			TS_ASSERT(delta1y > -0.001);
			TS_ASSERT(delta2x < 0.001);
			TS_ASSERT(delta2x > -0.001);
			TS_ASSERT(delta2y < 0.001);
			TS_ASSERT(delta2y > -0.001);
		
			std::cout << "Dont fall test pass";
		}
		
		void test_more_than_45_degress_fall(void){
			std::cout << "\nStarting fall test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.8f); //more than 45 degress
			Gusano gusano(world, 2.0f, 1.79f, 0.8f);
			
			Viga viga2(world, 10.0f, 0.0f, -0.8f); //less than -45 degress
			Gusano gusano2(world, 11.0f, -0.27f, -0.8f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			b2Vec2 position11 = gusano.GetPosition();
			b2Vec2 position21 = gusano2.GetPosition();
			for (int i = 0; i < 20; i++){
				//give some time to see if fall
				world.Step(timeStep, velocityIterations, positionIterations);
			}
			
			b2Vec2 position12 = gusano.GetPosition();
			b2Vec2 position22 = gusano2.GetPosition();
			
			float delta1x = position12.x - position11.x;
			float delta1y = position12.y - position11.y;
			float delta2x = position22.x - position21.x;
			float delta2y = position22.y - position21.y;
			TS_ASSERT(delta1x > 0.2 || delta1x < -0.2);
			TS_ASSERT(delta1y > 0.2 || delta1y < -0.2);
			TS_ASSERT(delta2x > 0.2 || delta2x < -0.2);
			TS_ASSERT(delta2y > 0.2 || delta2y < -0.2);
		
			//TS_ASSERT_DIFFERS(position12.x, position11.x);
			//TS_ASSERT_DIFFERS(position12.y, position11.y);
			//TS_ASSERT_DIFFERS(position22.x, position21.x);
			//TS_ASSERT_DIFFERS(position22.y, position21.y);
		
			std::cout << "Fall test pass";
		}
		
		void test_one_step_inclined(void){
			std::cout << "\nStarting one step inclined test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.5f);
			Gusano gusano(world, 2.0f, 1.67f, 0.5f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			b2Vec2 position1 = gusano.GetPosition();
			float32 angle1 = gusano.GetAngle();
			
			gusano.move(RIGHT);
			
			while(!gusano.isInactive()){
				world.Step(timeStep, velocityIterations, positionIterations);
				gusano.sumOneStep();
			}
			
			b2Vec2 position2 = gusano.GetPosition();
			float32 angle2 = gusano.GetAngle();
			TS_ASSERT_EQUALS(angle1, angle2);
			float deltax =  position2.x - position1.x;
			float deltay =  position2.y - position1.y;
			float delta = sqrt(pow(deltax,2) + pow(deltay,2));
			TS_ASSERT(delta < 0.101f);
			TS_ASSERT(delta > 0.098f); //the position of box2D can be not exact
		
			std::cout << "One step inclined test pass";
		}
		
		void test_one_step_declined(void){
			std::cout << "\nStarting one step declined test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, -0.5f);
			Gusano gusano(world, 2.0f, -0.48f, -0.5f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			b2Vec2 position1 = gusano.GetPosition();
			float32 angle1 = gusano.GetAngle();
			
			gusano.move(RIGHT);
			
			while(!gusano.isInactive()){
				world.Step(timeStep, velocityIterations, positionIterations);
				gusano.sumOneStep();
			}
			
			b2Vec2 position2 = gusano.GetPosition();
			float32 angle2 = gusano.GetAngle();
			TS_ASSERT_EQUALS(angle1, angle2);
			float deltax =  position2.x - position1.x;
			float deltay =  position2.y - position1.y;
			float delta = sqrt(pow(deltax,2) + pow(deltay,2));
			TS_ASSERT(delta < 0.101f);
			TS_ASSERT(delta > 0.098f); //the position of box2D can be not exact
		
			std::cout << "One step declined test pass";
		}
		
		void test_fall_when_finish_beam(void){
			std::cout << "\nStarting fall when finish beam test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.0f);
			Viga viga2(world, 6.00f, -2.0f, 0.0f);
			Gusano gusano(world, 6.23f, 0.52f, 0.0f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			b2Vec2 position1 = gusano.GetPosition();
			float32 angle1 = gusano.GetAngle();
			
			gusano.move(RIGHT);
			
			while(!gusano.isInactive()){
				world.Step(timeStep, velocityIterations, positionIterations);
				gusano.sumOneStep();
			}
			
			b2Vec2 position2 = gusano.GetPosition();
			float32 angle2 = gusano.GetAngle();
			std::cout << position2.y << "\n";
			TS_ASSERT_EQUALS(angle1, angle2);
			TS_ASSERT(position2.y < -1.48f);
			TS_ASSERT(position2.y > -1.50f); //the position of box2D can be not exact
			TS_ASSERT(position2.x < 6.28f);
			TS_ASSERT(position2.x > 6.27f); //the position of box2D can be not exact
		
			std::cout << "Fall when finish beam test pass";
		}
		
		void test_take_ground_angle(void){
			std::cout << "\nStarting take ground angle test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.50f);
			Gusano gusano(world, 3.0f, 2.29f, 0.0f);
			
			//esto es porque en el primer step van a entrar en contacto todos los bodys con el terreno
			world.Step(timeStep, velocityIterations, positionIterations);
			
			while(!gusano.isInactive()){
				world.Step(timeStep, velocityIterations, positionIterations);
				gusano.sumOneStep();
			}
			
			float32 angle2 = gusano.GetAngle();
			TS_ASSERT(angle2 < 0.51);
			TS_ASSERT(angle2 > 0.49);
		
			std::cout << "Take ground angle test pass";
		}
		
		void test_fall_and_take_ground_angle_when_land(void){
			std::cout << "\nStarting fall and take ground angle when land test\n";
			b2Vec2 gravity(0.0f, -10.0f);
			b2World world(gravity);
			ContactListener contact_listener;
			world.SetContactListener(&contact_listener);
				
			Viga viga(world, 0.0f, 0.0f, 0.50f);
			Gusano gusano(world, 3.0f, 3.0f, 0.0f);
			
			while(!gusano.isInactive()){
				world.Step(timeStep, velocityIterations, positionIterations);
				gusano.sumOneStep();
			}
			
			float32 angle2 = gusano.GetAngle();
			TS_ASSERT(angle2 < 0.511);
			TS_ASSERT(angle2 > 0.489);
		
			std::cout << "Fall and take ground angle when land test pass";
		}
		
};
