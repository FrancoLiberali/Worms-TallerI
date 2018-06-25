#include "game/gusano/gusano_body.h"

#define GUSANO_ANGULAR_DAMPING 2
#define GUSANO_DENSITY 6
#define GUSANO_FRICTION 0.2
#define GUSANO_RESTITUTION 0.2
#define GUSANO_HEIGHT 0.5
#define GUSANO_WIDHT 0.25
#define GUSANO_MIDDLE 0.0
#define NO_WEIGHT 0
#define NO_RESTITUTION 0
#define NO_ANGLE 0

#define LESS_THAN_GUSANO_HEIGHT 0.45
#define SENSOR_HEIGHT 0.1
#define SENSOR_WIDHT 0.00001
#define SENSOR_GROUP -5

#define SI_GRAVEDAD 1
#define NO_GRAVEDAD 0
#define JUMP_X_VEL sqrt(2.5)
#define JUMP_Y_VEL sqrt(10.2)
#define BACK_JUMP_X_VEL (1.0/sqrt(24.0))
#define BACK_JUMP_Y_VEL sqrt(24.8f)
#define LITTLE_VEL -0.1
#define GUSANO_VEL 0.2

GusanoBody::GusanoBody(b2World& world_e, float x, float y, float angle, UserData* user_data) : 
		world(world_e){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;
	this->body = this->world.CreateBody(&bodyDef);
	this->body->SetUserData((void*)user_data);
	this->body->SetTransform(this->body->GetPosition(), angle);
	this->body->SetAngularDamping(GUSANO_ANGULAR_DAMPING);
	
	b2Vec2 vertices[3];
	vertices[0].Set(GUSANO_MIDDLE, -GUSANO_HEIGHT);
	vertices[1].Set(GUSANO_WIDHT, GUSANO_HEIGHT);
	vertices[2].Set(-GUSANO_WIDHT, GUSANO_HEIGHT);
	int32 count = 3;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = GUSANO_DENSITY;
	fixtureDef.friction = GUSANO_FRICTION;
	fixtureDef.restitution = GUSANO_RESTITUTION;

	this->body->CreateFixture(&fixtureDef);
	
    dynamicBox.SetAsBox(SENSOR_WIDHT, SENSOR_HEIGHT, b2Vec2(GUSANO_MIDDLE, -LESS_THAN_GUSANO_HEIGHT), NO_ANGLE);
    fixtureDef.density = NO_WEIGHT;
    fixtureDef.restitution = NO_RESTITUTION;
    fixtureDef.isSensor = true;
    fixtureDef.filter.groupIndex = SENSOR_GROUP;
    b2Fixture* footSensorFixture = this->body->CreateFixture(&fixtureDef);
    this->foot_sensor_data = new int(FOOT_SENSOR_DATA);
    footSensorFixture->SetUserData((void*)this->foot_sensor_data);
    
    //add head sensor fixture	
    dynamicBox.SetAsBox(SENSOR_WIDHT, SENSOR_HEIGHT, b2Vec2(GUSANO_MIDDLE, LESS_THAN_GUSANO_HEIGHT), NO_ANGLE);
    fixtureDef.isSensor = true;
    b2Fixture* headSensorFixture = this->body->CreateFixture(&fixtureDef);
    this->head_sensor_data = new int(HEAD_SENSOR_DATA);
    headSensorFixture->SetUserData((void*)this->head_sensor_data);
}

GusanoBody::~GusanoBody(){
	if (this->foot_sensor_data){
		delete this->foot_sensor_data;
	}
	if (this->head_sensor_data){
		delete this->head_sensor_data;
	}
	if (this->body){
		this->world.DestroyBody(this->body);
	}
}

GusanoBody::GusanoBody(GusanoBody&& other) : world(other.world), body(other.body), 
		foot_sensor_data(other.foot_sensor_data),
		head_sensor_data(other.head_sensor_data){
	other.body = nullptr;
	other.foot_sensor_data = nullptr;
	other.head_sensor_data = nullptr;
}

GusanoBody& GusanoBody::operator=(GusanoBody&& other){
	this->body = other.body;
	other.body = nullptr;
	this->foot_sensor_data = other.foot_sensor_data;
	other.foot_sensor_data = nullptr;
	this->head_sensor_data = other.head_sensor_data;
	other.head_sensor_data = nullptr;
	
	return *this;
}

void GusanoBody::setUserData(UserData* user_data){
	this->body->SetUserData((void*)user_data);
}

b2Vec2 GusanoBody::GetPosition(){
	return this->body->GetPosition();
}

float32 GusanoBody::GetAngle(){
	return this->body->GetAngle();
}

b2Vec2 GusanoBody::getLinearVelocity(){
	return this->body->GetLinearVelocity();
}

void GusanoBody::cancelMovement(){
	this->body->SetGravityScale(NO_GRAVEDAD);
	this->body->SetLinearVelocity(b2Vec2(0,0));
	this->body->SetAngularVelocity(0);
	this->body->SetFixedRotation(true);
}

void GusanoBody::move(int dir){
	float angle = this->GetAngle();
	b2Vec2 vel;
	vel.x = GUSANO_VEL * dir * cos(angle);
	vel.y = GUSANO_VEL * dir * sin(angle);
	this->body->SetLinearVelocity(vel);
}

void GusanoBody::jump(int dir){
	// el cuerpo del gusano solo sufre la accion de la gravedad cuando no este inactivo
	this->body->SetGravityScale(SI_GRAVEDAD);
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = JUMP_X_VEL * dir;
    vel.y = JUMP_Y_VEL;
    this->body->SetLinearVelocity(vel);
}

void GusanoBody::backJump(int dir){
	// el gusano solo sufre la accion de la gravedad cuando no este inactivo
	this->body->SetGravityScale(SI_GRAVEDAD);
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = BACK_JUMP_X_VEL * -dir;
    vel.y = BACK_JUMP_Y_VEL;
    this->body->SetLinearVelocity(vel);
}

void GusanoBody::setGravity(){
	this->body->SetGravityScale(SI_GRAVEDAD);
	//se setea una pequenia velocidad para que el world lo comience a tener en cuenta para la simulacion
	this->body->SetLinearVelocity(b2Vec2(0, LITTLE_VEL));
	this->body->SetFixedRotation(false);
}

void GusanoBody::applyExplotion(b2Vec2 apply_point, b2Vec2 impulse){
	this->setGravity();
	this->body->ApplyLinearImpulse(impulse, apply_point, true);
}

void GusanoBody::teleport(b2Vec2 new_position, float angle){
	this->setGravity();
	this->body->SetTransform(new_position, angle);
}
