#include "Box2D/Box2D.h"
#include "gusano_state.h"
#include <vector>
#include "user_data.h"
#include "multiple_proxy.h"
#include "fake_proxy/mok_proxy.h"
#include <map>
#include <utility>
#include "projectile.h"

#ifndef __GUSANO_H__
#define __GUSANO_H__

class Gusano{
	private:
		b2World& world;
		MultipleProxy& proxy;
		std::vector<std::pair<int, int>>& to_remove_gusanos;
		b2Body* body;
		GusanoState* state;
		UserData* user_data;
		int* foot_sensor_data;
		int direction;
		std::vector<float> angles_list;
		std::pair<int, int> id;
		
		void rotateTo(float angle);
		
	public:
		Gusano(b2World& world_entry, MultipleProxy& proxy_e,
		std::vector<std::pair<int, int>>& to_remove_gusanos_e, float x, float y, float angle);
		
		~Gusano();
		
		void setId(int player, int number);
		
		b2Vec2 GetPosition();
		
		float32 GetAngle();
		
		int getDirection();
		
		void sendPosition();
		
		void move(int dir);
		
		void update();
		
		bool isInactive();
		
		bool isFalling();
		
		void jump();
		
		void backJump();
		
		void sink();
		
		void addLife(unsigned int life);
		
		void sufferDamage(unsigned int damage);
		
		void newContact(float ground_angle);
		
		void finishContact(float ground_angle);
		
		//b2Vec2 GetWorldVector(b2Vec2 local); 
		
		void applyExplotion(b2Vec2 apply_point, float damage, b2Vec2 impulse);
		
};

#endif
