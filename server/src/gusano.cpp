#include "gusano.h"
#include "inactive_state.h"
#include "moving_state.h"
#include "jumping_state.h"
#include "moving_finished.h"
#include "rotating_state.h"
#include "rotation_finished.h"
#include <cmath>
#include <iostream>

Gusano::Gusano(b2World& world_entry, float x, float y, float angle) : world(world_entry){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;
	this->body = this->world.CreateBody(&bodyDef);
	this->body->SetUserData((void*)this);
	this->body->SetTransform(this->body->GetPosition(), angle);
	
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.25f, 0.5f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	this->body->CreateFixture(&fixtureDef);
	
	//add foot sensor fixture
    dynamicBox.SetAsBox(0.25f, 0.1, b2Vec2(0,-0.42), 0);
    fixtureDef.density = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = this->body->CreateFixture(&fixtureDef);
    int* data = new int(1);
    footSensorFixture->SetUserData( (void*)data);
    
	this->state = new JumpingState(); //hasta que no haga contacto con el suelo esta saltando
	this->direccion = 1;
	this->cant_contacts = 0;
}

Gusano::~Gusano(){
	delete this->state;
}

b2Vec2 Gusano::GetPosition(){
	return this->body->GetPosition();
}

float32 Gusano::GetAngle(){
	return this->body->GetAngle();
}

void Gusano::move(int dir){
	if (this->direccion != dir){
		this->direccion = -this->direccion;
	} else {
		delete this->state;
		this->state = new MovingState();
		b2Vec2 vel;
		float angle = this->GetAngle();
		vel.x = 0.2f * this->direccion * cos(angle);
		vel.y = 0.2f * this->direccion * sin(angle);
		this->body->SetLinearVelocity(vel);
	}
}

void Gusano::sumOneStep(){
	try{
		this->state->sumOneStep();
	} catch (const MovingFinished& e){
		printf ("termina movimiento\n");
		delete this->state;
		this->state = new InactiveState();
		b2Vec2 vel = this->body->GetLinearVelocity();
		vel.x = 0.0f;
		vel.y = 0.0f;
		this->body->SetLinearVelocity(vel);
	} catch (const RotationFinished& e){
		printf ("termina rotacion\n");
		b2Vec2 vel = this->body->GetLinearVelocity();
		vel.x = 0.0f;
		vel.y = 0.0f;
		this->body->SetLinearVelocity(vel);
		this->body->SetGravityScale(0);
		this->body->SetFixedRotation(true);
		delete this->state;
		this->state = new InactiveState();
	}
}

bool Gusano::isInactive(){
	return (this->state->isInactive());
}

bool Gusano::isFalling(){
	return (this->state->isFalling());
}

void Gusano::jump(){
	delete this->state;
	this->state = new JumpingState();
	this->body->SetGravityScale(1);
	printf("state->cayendo\n");
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = b2Sqrt(2.5f) * this->direccion;
    vel.y = b2Sqrt(10.2f);
    this->body->SetLinearVelocity( vel );
}

void Gusano::backJump(){
	delete this->state;
	this->state = new JumpingState();
	this->body->SetGravityScale(1);
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = (1.0f/b2Sqrt(24.0f)) * (-(this->direccion));
    vel.y = b2Sqrt(24.8f);
    this->body->SetLinearVelocity( vel );
}

float radDiff( float a, float b )
   {
      return atan2( sin(a-b), cos(a-b) );
   }

void Gusano::newContact(float ground_angle){
	this->cant_contacts += 1;
	if (this->cant_contacts == 1){
		this->body->SetGravityScale(0);
		this->body->SetLinearVelocity(b2Vec2(0,0));
		printf("state->inactivo\n");
		delete this->state;
		this->state = new InactiveState();
		if (this->GetAngle() != ground_angle){
			printf ("arreglar angulo\n");
			delete this->state;
			this->state = new RotatingState(this->body, ground_angle);
			this->body->SetGravityScale(1);
			this->body->SetFixedRotation(false);
			float ang_imp = this->body->GetInertia() * radDiff(ground_angle, this->body->GetAngle());
			this->body->ApplyAngularImpulse(ang_imp, true);
		}
	} else {
		std::cout << "TOCO al segundo \n";
		//this->body->SetLinearVelocity(b2Vec2(0,0));
		//this->body->SetTransform(this->body->GetPosition(), 0);
	}
}

void Gusano::finishContact(){
	this->cant_contacts -= 1;
	if (this->cant_contacts == 0 && !(this->isFalling())){
		std::cout << "state->falling\n";
		delete this->state;
		this->state = new JumpingState();
		this->body->SetGravityScale(1);
		b2Vec2 vel = this->body->GetLinearVelocity();
		vel.x = 0.0f;
		this->body->SetLinearVelocity(vel);
	}
}
		
		
		
		
		
		
		
