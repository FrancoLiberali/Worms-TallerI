#include "water.h"

Water::Water(b2World& world, float x_from, float y_from, float x_to, float y_to){
	b2BodyDef water_body_def;
	b2Body* water_body = world.CreateBody(&water_body_def);
	this->user_data = new UserData(2, nullptr);
	water_body->SetUserData((void*)this->user_data);
	
	b2FixtureDef water_fixture_def;
    b2EdgeShape edge_shape;
    water_fixture_def.shape = &edge_shape;
    water_fixture_def.filter.groupIndex = -2;
    edge_shape.Set(b2Vec2(x_from, y_from), b2Vec2(x_to, y_to));
    water_body->CreateFixture(&water_fixture_def);
}

Water::~Water(){
	delete this->user_data;
}
