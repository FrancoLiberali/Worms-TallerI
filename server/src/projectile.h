#include "Box2D/Box2D.h"
#include <vector>
#include "user_data.h"

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

class Projectile {
	protected:
		b2World& world;
		b2Body* body;
		const int damage;
		const int radius;
		std::vector<Projectile*>& to_remove;
		UserData* user_data;
		
		void create(float x, float y, float angle, float vel, int type);
		
	public:
		Projectile(b2World& world_entry, int damage_e, int radius_e, std::vector<Projectile*>& to_remove_e);
		
		Projectile(b2World& world_entry, float x, float y, float angle, float vel,
				   int damage_e, int radius_e, int type, std::vector<Projectile*>& to_remove_e);
		
		~Projectile();
		
		virtual void exploit();
		
		virtual void update() = 0;
		
		b2Vec2 GetPosition(){ return this->body->GetPosition();}
		
		float32 GetAngle(){ return this->body->GetAngle();}
		
		void sink();
};

#endif
