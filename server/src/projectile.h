#include "Box2D/Box2D.h"
#include <vector>
#include "user_data.h"
#include "fake_proxy/mok_proxy.h"
#include <map>

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

class Projectile {
	protected:
		b2World& world;
		int number;
		b2Body* body;
		const int damage;
		const int radius;
		std::map<int, Projectile*>& to_remove;
		MokProxy& proxy;
		UserData* user_data;
		
	public:		
		Projectile(b2World& world_entry, int number, float x, float y, float angle, float vel,
				   int damage_e, int radius_e, int type, std::map<int, Projectile*>& to_remove_e, MokProxy& proxy_e);
		
		~Projectile();
		
		virtual void exploit();
		
		virtual void update() = 0;
		
		b2Vec2 GetPosition(){ return this->body->GetPosition();}
		
		float32 GetAngle(){ return this->body->GetAngle();}
		
		void sink();
};

#endif
