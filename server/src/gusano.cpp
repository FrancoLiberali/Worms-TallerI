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

Gusano::Gusano(b2World& world_entry, float x, float y, float angle) : world(world_entry){
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
    int data = 1;
    footSensorFixture->SetUserData((void*)&data);
	
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
	
	
    
	this->state = new JumpingState(); //hasta que no haga contacto con el suelo esta saltando
	this->direccion = 1;
}

Gusano::~Gusano(){
	delete this->state;
	delete this->user_data;
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
		this->body->SetLinearVelocity(b2Vec2(0,0));
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

/*float radDiff( float a, float b )
   {
      return atan2( sin(a-b), cos(a-b) );
   }*/

void Gusano::newContact(float ground_angle){
	this->angles_list.push_back(ground_angle);
	int cant_contacts = angles_list.size();
	if (cant_contacts == 1){
		this->body->SetGravityScale(0);
		this->body->SetLinearVelocity(b2Vec2(0,0));
		printf("state->inactivo\n");
		delete this->state;
		this->state = new InactiveState();
		if (this->GetAngle() != ground_angle){
			printf ("arreglar angulo\n");
			std::cout << ground_angle << "\n";
			delete this->state;
			this->state = new RotatingState(this->body, this->GetPosition(), ground_angle);
			/*delete this->state;
			this->state = new RotatingState(this->body, ground_angle);
			this->body->SetGravityScale(1);
			this->body->SetFixedRotation(false);
			float ang_imp = this->body->GetInertia() * radDiff(ground_angle, this->body->GetAngle());
			std::cout << ang_imp << "\n";
			this->body->ApplyAngularImpulse(ang_imp, true);*/
		}
	} else if (cant_contacts == 2){
		std::cout << "TOCO al segundo \n";
		std::cout << ground_angle << "\n";
	}
}

void Gusano::finishContact(float ground_angle){
	std::vector<float>::iterator it;
	it = std::find(this->angles_list.begin(), this->angles_list.end(), ground_angle);
    this->angles_list.erase(it);
	int cant_contacts = angles_list.size();
	if (cant_contacts == 0 && !(this->isFalling())){
		std::cout << "state->falling\n";
		delete this->state;
		this->state = new JumpingState();
		this->body->SetGravityScale(1);
		//b2Vec2 vel = this->body->GetLinearVelocity();
		//vel.x = 0.0f;
		//this->body->SetLinearVelocity(vel);
	}
	if (cant_contacts == 1){
		printf("solo toca a 1\n");
		std::cout << "deja de tocar a :" << ground_angle << "\n";
		if (this->GetAngle() != angles_list.back()){
			delete this->state;
			this->state = new RotatingState(this->body, this->GetPosition(), angles_list.back());
			printf ("arreglar angulo\n");
			std::cout << angles_list.back() << "\n";
		}
	}
}

//b2Vec2 Gusano::GetWorldVector(b2Vec2 local){
	//return this->body->GetWorldVector(local);
//} 

void Gusano::applyExplotion(b2Vec2 apply_point, float damage, b2Vec2 impulse){
	//this->applyDamage(damage);
	std::cout << "volar por explosion \n";
    this->body->ApplyLinearImpulse(impulse, apply_point, true);
    delete this->state;
	this->state = new ExplotedState(this->body);
	this->body->SetGravityScale(1);
	this->body->SetFixedRotation(false);
}
		
		
		
		
		
		
