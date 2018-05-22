#include "Box2D/Box2D.h"
#include "gusano_state.h"
#include <vector>

#ifndef __GUSANO_H__
#define __GUSANO_H__

class Gusano{
	private:
		b2World& world;
		b2Body* body;
		GusanoState* state;
		int direccion;
		//std::vector<b2Body*> contacts_list;
		int cant_contacts;
		
	public:
		Gusano(b2World& world_entry, float x, float y, float angle);
		
		~Gusano();
		
		b2Vec2 GetPosition();
		
		float32 GetAngle();
		
		void move(int dir);
		
		void sumOneStep();
		
		bool isInactive();
		
		bool isFalling();
		
		void jump();
		
		void backJump();
		
		void newContact(float ground_angle);
		
		void finishContact();
		
};

#endif
