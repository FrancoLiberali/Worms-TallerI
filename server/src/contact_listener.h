#include "Box2D/Box2D.h"
#include "gusano.h"
#include "projectile.h"
#include "user_data.h"
#include <iostream>

#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

class ContactListener : public b2ContactListener{
	public:
		void BeginContact(b2Contact* contact);
					
		void EndContact(b2Contact* contact);
					
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif
