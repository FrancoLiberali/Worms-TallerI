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
	//fixtureDef.filter.categoryBits = 0x0010;
	//fixtureDef.filter.maskBits = 0x1001;
	fixtureDef.filter.groupIndex = -2;

	vigaBody->CreateFixture(&fixtureDef);
	proxy.sendVigaCreation((int)x * 1000, (int)y * 1000, (int)angle);
	
	/*b2BodyDef groundBodyDef;
	int* data = new int(0);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    groundBody->SetUserData((void*)data);
	
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.density = 0;
    myFixtureDef.friction = 0;
    b2EdgeShape edgeShape;
    myFixtureDef.shape = &edgeShape;
    myFixtureDef.filter.groupIndex = -1;
    float complement = PI/2 - angle;
    float cos_complement;
    if (angle == 0){
		cos_complement = 0.0;
	} else {
		cos_complement = cos(complement);
	}
	b2Vec2 v2(x + (6 * cos(angle)), y + (6 * sin(angle)));
	b2Vec2 v3(x + (6 * cos(angle)) + (0.8 * cos_complement), y + (6 * sin(angle)) - (0.8 * sin(PI/2 - angle)));
	b2Vec2 v4(x + (0.8 * cos_complement), y - (0.8 * sin(PI/2 - angle)));
	std::cout << x << ", " << y << "\n";
	std::cout << v2.x << ", " << v2.y << "\n";
	std::cout << v3.x << ", " << v3.y << "\n";
	std::cout << v4.x << ", " << v4.y << "\n";
    edgeShape.Set(b2Vec2(x,y), v2);
    groundBody->CreateFixture(&myFixtureDef);
    edgeShape.Set(v2, v3);
    groundBody->CreateFixture(&myFixtureDef);
    edgeShape.Set(v3, v4);
    groundBody->CreateFixture(&myFixtureDef);
    edgeShape.Set(v4, b2Vec2(x,y));
    groundBody->CreateFixture(&myFixtureDef);
    
    groundBody->SetTransform(groundBody->GetPosition(), angle);
    std::cout << "POSICION: " << groundBody->GetPosition().x << ", " << groundBody->GetPosition().y << "\n";
    std::cout << "ANGULO: " << groundBody->GetAngle() << "\n";*/
}

Viga::~Viga(){
}
