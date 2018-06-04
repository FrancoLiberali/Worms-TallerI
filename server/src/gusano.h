#include "Box2D/Box2D.h"
#include "gusano_state.h"
#include <vector>
#include "user_data.h"
#include "proxy.h"
#include "fake_proxy/mok_proxy.h"
#include <map>

#ifndef __GUSANO_H__
#define __GUSANO_H__

class Gusano{
	private:
		b2World& world;
		//Proxy& proxy;
		MokProxy& proxy;
		const unsigned int number;
		std::map<unsigned int, Gusano*>& to_remove_gusanos;
		b2Body* body;
		GusanoState* state;
		UserData* user_data;
		int* foot_sensor_data;
		int direction;
		std::vector<float> angles_list;
		
		void rotateTo(float angle);
		
	public:
		//Gusano(b2World& world_entry, Proxy& proxy_e, unsigned int number_e, 
		Gusano(b2World& world_entry, MokProxy& proxy_e, unsigned int number_e, 
		std::map<unsigned int, Gusano*>& to_remove_gusanos_e, float x, float y, float angle);
		
		~Gusano();
		
		b2Vec2 GetPosition();
		
		float32 GetAngle();
		
		int getDirection();
		
		unsigned int getNumber();
		
		void sendPosition();
		
		void move(int dir);
		
		void update();
		
		bool isInactive();
		
		bool isFalling();
		
		void jump();
		
		void backJump();
		
		void sink();
		
		void newContact(float ground_angle);
		
		void finishContact(float ground_angle);
		
		//b2Vec2 GetWorldVector(b2Vec2 local); 
		
		void applyExplotion(b2Vec2 apply_point, float damage, b2Vec2 impulse);
		
};

#endif
