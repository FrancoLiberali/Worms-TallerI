#include "gusano.h"
#include "inactive_state.h"
#include "moving_state.h"
#include "jumping_state.h"
#include "moving_finished.h"
#include "rotating_state.h"
#include "exploted_state.h"
#include <cmath>
#include <iostream>
#include <algorithm>

#define INACTIVE_STATE 0
#define MOVING_STATE 1
#define JUMPING_STATE 2
#define SINKING_STATE 3
#define DEAD_STATE 4

Gusano::Gusano(b2World& world_entry, MultipleProxy& proxy_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e, float x, float y, float angle) 
		: world(world_entry), proxy(proxy_e), to_remove_gusanos(to_remove_gusanos_e){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;
	this->body = this->world.CreateBody(&bodyDef);
	this->user_data = new UserData(1, this);
	this->body->SetUserData((void*)this->user_data);
	this->body->SetTransform(this->body->GetPosition(), angle);
	
	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, -0.5f);
	vertices[1].Set(0.25f, 0.5f);
	vertices[2].Set(-0.25f, 0.5f);
	
	int32 count = 3;

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, count);
	//dynamicBox.SetAsBox(0.25f, 0.375f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	//fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
	
	//add foot sensor fixture
	//vertices[0].Set(0.0f, -0.51f);
	//vertices[1].Set(0.01f, -0.47f);
	//vertices[2].Set(-0.01f, -0.47f);
	
    dynamicBox.SetAsBox(0.00001, 0.1, b2Vec2(0,-0.45), 0);
    //dynamicBox.Set(vertices, count);
    fixtureDef.density = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = this->body->CreateFixture(&fixtureDef);
    this->foot_sensor_data = new int(1);
    footSensorFixture->SetUserData((void*)this->foot_sensor_data);
    
    //add head sensor fixture	
    dynamicBox.SetAsBox(0.00001, 0.1, b2Vec2(0, 0.45), 0);
    fixtureDef.density = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.isSensor = true;
    b2Fixture* headSensorFixture = this->body->CreateFixture(&fixtureDef);
    this->head_sensor_data = new int(2);
    headSensorFixture->SetUserData((void*)this->head_sensor_data);
	
	/*//add wheel
	bodyDef.position.Set(x, y - 0.25);
	bodyDef.fixedRotation = false;
	this->wheel = this->world.CreateBody(&bodyDef);
	this->wheel->SetUserData((void*)this);
	
	b2CircleShape circleShape;
	circleShape.m_radius = 0.25;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.1f;

	this->wheel->CreateFixture(&fixtureDef);
	
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = this->body;
	revoluteJointDef.bodyB = this->wheel;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(0,-0.25);
	revoluteJointDef.localAnchorB.Set(0,0);
	this->world.CreateJoint(&revoluteJointDef);*/
	
	
    
	this->state = new JumpingState(this->body, this); //hasta que no haga contacto con el suelo esta saltando
	this->direction = 1;
}

Gusano::~Gusano(){
	delete this->state;
	delete this->user_data;
	delete this->foot_sensor_data;
	delete this->head_sensor_data;
	this->user_data = nullptr;
	this->foot_sensor_data = nullptr;
	this->world.DestroyBody(this->body);
}

void Gusano::setId(int player, int number){
	this->id.first = player;
	this->id.second = number;
	this->sendPosition();
}

b2Vec2 Gusano::GetPosition(){
	return this->body->GetPosition();
}

float32 Gusano::GetAngle(){
	return this->body->GetAngle();
}

int Gusano::getDirection(){
	return this->direction;
}

void Gusano::sendPosition(){
	b2Vec2 position = this->GetPosition();
	float32 angle = this->GetAngle();
	this->proxy.sendGusanoPosition(this->id.first, this->id.second, position.x, position.y, this->direction, angle);
}

void Gusano::move(int dir){
	if (this->direction != dir){
		this->direction = -this->direction;
		this->sendPosition();
	} else {
		delete this->state;
		this->state = new MovingState();
		this->proxy.send_state_change(this->id.first, this->id.second, MOVING_STATE);
		b2Vec2 vel;
		float angle = this->GetAngle();
		vel.x = 0.2f * this->direction * cos(angle);
		vel.y = 0.2f * this->direction * sin(angle);
		this->body->SetLinearVelocity(vel);
	}
}

void Gusano::cancelMovement(){
	this->body->SetLinearVelocity(b2Vec2(0,0));
	this->body->SetAngularVelocity(0);
}

void Gusano::update(){
	this->damaged = false;
	try{
		this->state->sumOneStep();
	} catch (const MovingFinished& e){
		printf ("termina movimiento\n");
		delete this->state;
		this->state = new InactiveState();
		this->body->SetLinearVelocity(b2Vec2(0,0));
		this->sendPosition();
		this->proxy.send_state_change(this->id.first, this->id.second, INACTIVE_STATE);
		if (this->head_in_contact && angles_list.size() == 0){
			std::cout << "de cabeza\n";
			this->rotateTo(this->GetAngle() - M_PI);
			this->head_in_contact = false;
		} else {
			this->rotateTo(angles_list.back());
		}
		this->body->SetFixedRotation(true);
	}
}

void Gusano::rotateTo(float angle){
	if (this->GetAngle() != angle){
		printf ("arreglar angulo\n");
		std::cout << angle << "\n";
		delete this->state;
		this->state = new RotatingState(this->body, this->GetPosition(), angle);
	}
}

bool Gusano::isInactive(){
	return (this->state->isInactive());
}

//bool Gusano::isFalling(){
	//return (this->state->isFalling());
//}

void Gusano::jump(){
	delete this->state;
	this->state = new JumpingState(this->body, this);
	this->proxy.send_state_change(this->id.first, this->id.second, JUMPING_STATE);
	this->body->SetGravityScale(1);
	printf("state->cayendo\n");
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = b2Sqrt(2.5f) * this->direction;
    vel.y = b2Sqrt(10.2f);
    this->body->SetLinearVelocity( vel );
}

void Gusano::backJump(){
	delete this->state;
	this->state = new JumpingState(this->body, this);
	this->body->SetGravityScale(1);
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = (1.0f/b2Sqrt(24.0f)) * (-(this->direction));
    vel.y = b2Sqrt(24.8f);
    this->body->SetLinearVelocity( vel );
}

void Gusano::sink(){
	this->sendPosition();
	this->proxy.send_state_change(this->id.first, this->id.second, SINKING_STATE);
	this->to_remove_gusanos.push_back(this->id);
}

void Gusano::addLife(unsigned int to_add){
	this->life += to_add;
	this->proxy.sendLifeChange(this->id.first, this->id.second, this->life);
}

void Gusano::sufferDamage(unsigned int damage){
	if (!this->state->isExploted()){
		this->life -= damage;
		this->damaged = true;
		this->proxy.sendLifeChange(this->id.first, this->id.second, this->life);
		if (this->life <= 0){
			this->sendPosition();
			this->proxy.send_state_change(this->id.first, this->id.second, DEAD_STATE);
			this->to_remove_gusanos.push_back(this->id);
		}
	}
}

bool Gusano::gotDamaged(){
	return this->damaged;
}

/*float radDiff( float a, float b )
   {
      return atan2( sin(a-b), cos(a-b) );
   }*/

void Gusano::newContact(float ground_angle){
	this->angles_list.push_back(ground_angle);
	int cant_contacts = angles_list.size();
	if (cant_contacts == 1){
		printf("state->inactivo\n");
		this->state->sumOneStep();
		delete this->state;
		this->state = new InactiveState();
		this->body->SetGravityScale(0);
		this->body->SetLinearVelocity(b2Vec2(0,0));
		this->proxy.send_state_change(this->id.first, this->id.second, INACTIVE_STATE);
		this->rotateTo(ground_angle);
	} else if (cant_contacts == 2){
		std::cout << "TOCO al segundo \n";
		std::cout << ground_angle << "\n";
	}
}

void Gusano::headContact(){
	this->head_in_contact = true;
}

void Gusano::finishContact(float ground_angle){
	std::vector<float>::iterator it;
	it = std::find(this->angles_list.begin(), this->angles_list.end(), ground_angle);
    this->angles_list.erase(it);
	int cant_contacts = angles_list.size();
	if (cant_contacts == 0 && !(this->state->isFalling())){
		std::cout << "state->falling\n";
		delete this->state;
		this->state = new JumpingState(this->body, this);
		this->proxy.send_state_change(this->id.first, this->id.second, JUMPING_STATE);
		this->body->SetGravityScale(1);
		//b2Vec2 vel = this->body->GetLinearVelocity();
		//vel.x = 0.0f;
		//this->body->SetLinearVelocity(vel);
	}
	if (cant_contacts == 1){
		printf("solo toca a 1\n");
		std::cout << "deja de tocar a :" << ground_angle << "\n";
		this->rotateTo(angles_list.back());
	}
}

void Gusano::headFinishContact(){
	this->head_in_contact = false;
}

//b2Vec2 Gusano::GetWorldVector(b2Vec2 local){
	//return this->body->GetWorldVector(local);
//} 

void Gusano::applyExplotion(b2Vec2 apply_point, float damage, b2Vec2 impulse){
	this->sufferDamage(damage);
	std::cout << "volar por explosion \n";
    this->body->ApplyLinearImpulse(impulse, apply_point, true);
    delete this->state;
	this->state = new ExplotedState(this->body);
	this->body->SetGravityScale(1);
	this->body->SetFixedRotation(false);
}
		
		
		
		
		
		
