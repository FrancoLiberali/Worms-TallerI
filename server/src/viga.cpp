#include "viga.h"
#include <iostream>
#include <cmath>

#define PI 3.1415927
Viga::Viga(b2World& world, float x, float y, float angle, MultipleProxy& proxy) {
	b2BodyDef vigaBodyDef;
	//vigaBodyDef.position.Set(x, y);
	//int* data = new int(0);
	b2Body* vigaBody = world.CreateBody(&vigaBodyDef);
	//vigaBody->SetUserData((void*)data);
	float x_center; 
	float y_center;
	if (angle <= 0){
		x_center = x + cos(angle - atan(0.8/6)) * sqrt(pow(0.8,2) + pow(6,2)) / 2; 
		y_center = y + sin(angle - atan(0.8/6)) * sqrt(pow(0.8,2) + pow(6,2)) / 2;
	} else {
		x_center = x + 0.8 * sin(angle) + cos(angle + atan(0.8/6)) * sqrt(pow(0.8,2) + pow(6,2)) / 2; 
		y_center = y - 0.8 * cos(angle) + sin(angle + atan(0.8/6)) * sqrt(pow(0.8,2) + pow(6,2)) / 2; 
	}
	vigaBody->SetTransform(b2Vec2(x_center, y_center), angle);
	
	b2PolygonShape vigaBox;
	vigaBox.SetAsBox(3.0f, 0.4f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &vigaBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.filter.groupIndex = -2;

	vigaBody->CreateFixture(&fixtureDef);
	proxy.sendVigaCreation((int)x * 1000, (int)y * 1000, (int)angle);
}

Viga::~Viga(){
}
