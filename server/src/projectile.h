#include "Box2D/Box2D.h"

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

class Projectile {
	private:
		b2World& world;
		b2Body* body;
		const int damage;
		const int radius;
		
	public:
		Projectile(b2World& world_entry, float x, float y, float angle, float vel, int damage_e, int radius_e);
		
		~Projectile();
		
		void exploit();
		
		b2Vec2 GetPosition(){ return this->body->GetPosition();}
		
		float32 GetAngle(){ return this->body->GetAngle();}
};

#endif
