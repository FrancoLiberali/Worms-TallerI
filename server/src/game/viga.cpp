#include "game/viga.h"
#include <iostream>
#include <cmath>

#define BIG_WIDTH 3.0
#define SHORT_WIDTH 1.5
#define BIG_HEIGHT 0.4
#define SHORT_HEIGHT 0.4
#define VIGA_DENSITY 0
#define VIGA_FRICTION 1
#define VIGA_GROUP -2

Viga::Viga(b2World& world, float x, float y, float angle, MultipleProxy& proxy, bool big) {
	b2BodyDef vigaBodyDef;
	vigaBodyDef.position.Set(x, y);
	b2Body* vigaBody = world.CreateBody(&vigaBodyDef);
	vigaBody->SetTransform(b2Vec2(x, y), angle);
	
	b2PolygonShape vigaBox;
	if (big){
		vigaBox.SetAsBox(BIG_WIDTH, BIG_HEIGHT);
	} else {
		vigaBox.SetAsBox(SHORT_WIDTH, SHORT_HEIGHT);
	}
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &vigaBox;
	fixtureDef.density = VIGA_DENSITY;
	fixtureDef.friction = VIGA_FRICTION;
	fixtureDef.filter.groupIndex = VIGA_GROUP;

	vigaBody->CreateFixture(&fixtureDef);
	proxy.sendVigaCreation(x, y, angle);
}

Viga::~Viga(){
}
