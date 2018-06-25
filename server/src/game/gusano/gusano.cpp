#include "game/gusano/gusano.h"
#include "game/gusano/inactive_state.h"
#include "game/gusano/moving_state.h"
#include "game/gusano/jumping_state.h"
#include "game/gusano/moving_finished.h"
#include "game/gusano/rotating_finished.h"
#include "game/gusano/rotating_state.h"
#include "game/gusano/exploted_state.h"
#include <cmath>
#include <iostream>
#include <algorithm>

#define GUSANO_ANGULAR_DAMPING 2
#define GUSANO_DENSITY 6
#define GUSANO_FRICTION 0.2
#define GUSANO_RESTITUTION 0.2
#define GUSANO_HEIGHT 0.5
#define GUSANO_WIDHT 0.25
#define GUSANO_MIDDLE 0.0
#define NO_ANGLE 0
#define LESS_THAN_GUSANO_HEIGHT 0.45
#define SENSOR_HEIGHT 0.1
#define SENSOR_WIDHT 0.00001
#define SENSOR_GROUP -5
#define RIGHT 1

#define NO_WEIGHT 0
#define NO_RESTITUTION 0

#define INACTIVE_STATE 0
#define MOVING_STATE 1
#define JUMPING_STATE 2
#define DEAD_STATE 4
#define EXPLOTION_STATE 5

#define SI_GRAVEDAD 1
#define NO_GRAVEDAD 0
#define JUMP_X_VEL sqrt(2.5)
#define JUMP_Y_VEL sqrt(10.2)
#define BACK_JUMP_X_VEL (1.0/sqrt(24.0))
#define BACK_JUMP_Y_VEL sqrt(24.8f)
#define LITTLE_VEL -0.1
#define MUCHO 3000

Gusano::Gusano(b2World& world_entry, MultipleProxy& proxy_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e, float x, float y, float angle, int life_e) 
		: world(world_entry), proxy(proxy_e), to_remove_gusanos(to_remove_gusanos_e), 
			user_data(GUSANO_INDICATOR, this), life(life_e){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;
	this->body = this->world.CreateBody(&bodyDef);
	this->body->SetUserData((void*)&this->user_data);
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
	
	this->state = new JumpingState(this->body, this); //hasta que no haga contacto con el suelo esta saltando
	this->direction = RIGHT;
}

Gusano::Gusano(Gusano&& other) : world(other.world), proxy(other.proxy), to_remove_gusanos(other.to_remove_gusanos),
		body(other.body), state(other.state), user_data(other.user_data), 
		foot_sensor_data(other.foot_sensor_data),
		head_sensor_data(other.head_sensor_data), direction(other.direction), number(other.number), id(other.id), life(other.life){
	other.state = nullptr;
	other.body = nullptr;
	other.foot_sensor_data = nullptr;
	other.head_sensor_data = nullptr;
	this->user_data.pointer = this;
	this->body->SetUserData((void*)&this->user_data);
}

Gusano& Gusano::operator=(Gusano&& other){
	this->body = other.body;
	other.body = nullptr;
	this->state = other.state;
	other.state = nullptr;
	this->user_data = other.user_data;
	this->user_data.pointer = this;
	this->foot_sensor_data = other.foot_sensor_data;
	other.foot_sensor_data = nullptr;
	this->head_sensor_data = other.head_sensor_data;
	other.head_sensor_data = nullptr;
	this->body->SetUserData((void*)&this->user_data);
	this->life = other.life;
	
	return *this;
}

Gusano::~Gusano(){
	if (this->state){
		delete this->state;
	}
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

void Gusano::setId(int player, int number_e, int id_e){
	this->number.first = player;
	this->number.second = number_e;
	this->id = id_e;
	b2Vec2 position = this->GetPosition();
	float32 angle = this->GetAngle();
	// para el cliente el gusano se crea recien cuando existe una forma de identificarlo
	this->proxy.sendGusanoCreation(this->id, player, position.x, position.y, this->direction, angle);
}

int Gusano::getId(){
	return this->id;
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
	this->proxy.sendGusanoPosition(this->id, position.x, position.y, this->direction, angle);
}

void Gusano::move(int dir){
	this->state->move(this->state, dir, this->direction, this->id, this->GetPosition(), this->GetAngle(), this->proxy, this->body);
}

void Gusano::cancelMovement(){
	this->body->SetLinearVelocity(b2Vec2(0,0));
	this->body->SetAngularVelocity(0);
}

void Gusano::update(){
	this->damage_suffered = 0;
	try{
		this->state->update();
	} catch (const MovingFinished& e){
		delete this->state;
		this->state = new InactiveState();
		this->body->SetLinearVelocity(b2Vec2(0,0));
		this->sendPosition();
		this->proxy.sendStateChange(this->id, INACTIVE_STATE);
		// si quedo de cabeza
		if (this->head_in_contact && angles_list.size() == 0){
			// esta de cabeza y hay que girarlo
			this->rotateTo(this->GetAngle() - M_PI);
			this->head_in_contact = false;
		} else if (angles_list.size() == 0){
			this->rotateTo(NO_ANGLE);
		} else {
			this->rotateTo(angles_list.back());
		}
		this->body->SetFixedRotation(true);
	} catch (const RotatingFinished& e){
		delete this->state;
		this->state = new InactiveState();
		this->body->SetLinearVelocity(b2Vec2(0,0));
		this->sendPosition();
	}
}

void Gusano::rotateTo(float angle){
	if (this->GetAngle() != angle){
		delete this->state;
		this->state = new RotatingState(this->body, this->GetPosition(), angle);
		this->proxy.sendStateChange(this->id, INACTIVE_STATE);
	}
}

bool Gusano::isInactive(){
	return (this->state->isInactive());
}

void Gusano::jump(){
	delete this->state;
	this->state = new JumpingState(this->body, this);
	this->proxy.sendStateChange(this->id, JUMPING_STATE);
	// el gusano solo sufre la accion de la gravedad cuando no este inactivo
	this->body->SetGravityScale(SI_GRAVEDAD);
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = JUMP_X_VEL * this->direction;
    vel.y = JUMP_Y_VEL;
    this->body->SetLinearVelocity(vel);
}

void Gusano::backJump(){
	delete this->state;
	this->state = new JumpingState(this->body, this);
	this->proxy.sendStateChange(this->id, JUMPING_STATE);
	// el gusano solo sufre la accion de la gravedad cuando no este inactivo
	this->body->SetGravityScale(SI_GRAVEDAD);
	b2Vec2 vel = this->body->GetLinearVelocity();
	vel.x = BACK_JUMP_X_VEL * (-(this->direction));
    vel.y = BACK_JUMP_Y_VEL;
    this->body->SetLinearVelocity(vel);
}

void Gusano::destroy(){
	//para que no mande danio despues de muerto
	this->damage_suffered = MUCHO;
	this->sendPosition();
	this->proxy.sendStateChange(this->id, DEAD_STATE);
	this->to_remove_gusanos.push_back(this->number);
}

void Gusano::addLife(unsigned int to_add){
	this->life += to_add;
	this->proxy.sendLifeChange(this->id, this->life);
}

void Gusano::sufferDamage(unsigned int damage){
	if (damage > this->damage_suffered){
		this->life -= (damage - this->damage_suffered);
		this->damage_suffered = damage;
		if (this->life <= 0){
			this->proxy.sendLifeChange(this->id, 0);
			this->destroy();
		} else {
			this->proxy.sendLifeChange(this->id, this->life);
		}
	}
}

bool Gusano::gotDamaged(){
	return (this->damage_suffered > 0);
}

void Gusano::newContact(float ground_angle){
	// se guarda en el lista los angulos de las cosas sobre las que el gusano esta parado
	this->angles_list.push_back(ground_angle);
	int cant_contacts = angles_list.size();
	if (cant_contacts == 1 && !(this->state->isExploted())){
		//significa que antes estaba en el aire y toco el suelo
		this->state->update();
		delete this->state;
		this->state = new InactiveState();
		this->body->SetGravityScale(NO_GRAVEDAD);
		this->body->SetLinearVelocity(b2Vec2(0,0));
		this->body->SetAngularVelocity(0);
		this->proxy.sendStateChange(this->id, INACTIVE_STATE);
		this->rotateTo(ground_angle);
	}
}

void Gusano::headContact(){
	this->head_in_contact = true;
}

void Gusano::finishContact(float ground_angle){
	std::vector<float>::iterator it;
	it = std::find(this->angles_list.begin(), this->angles_list.end(), ground_angle);
	if (it != this->angles_list.end()){
		this->angles_list.erase(it);
	}
	int cant_contacts = angles_list.size();
	if (cant_contacts == 0 && !(this->state->isFalling()) && !(this->state->isExploted())){
		delete this->state;
		this->state = new JumpingState(this->body, this);
		this->proxy.sendStateChange(this->id, JUMPING_STATE);
		this->body->SetGravityScale(SI_GRAVEDAD);
		//se setea una pequenia velocidad para que el world lo comience a tener en cuenta para la simulacion
		this->body->SetLinearVelocity(b2Vec2(0, LITTLE_VEL));
	} else if (cant_contacts == 1){
		if (!(this->state->isFalling()) && !(this->state->isExploted())){
			this->rotateTo(angles_list.back());
		}
	}
}

void Gusano::headFinishContact(){
	this->head_in_contact = false;
}

void Gusano::applyExplotion(b2Vec2 apply_point, float damage, b2Vec2 impulse){
	this->sufferDamage(damage);
	this->body->ApplyLinearImpulse(impulse, apply_point, true);
	if (!(this->state->isExploted())){
		delete this->state;
		this->state = new ExplotedState(this->body);
		this->proxy.sendStateChange(this->id, EXPLOTION_STATE);
		this->body->SetGravityScale(SI_GRAVEDAD);
		this->body->SetFixedRotation(false);
	}
}

void Gusano::teleport(b2Vec2 new_position){
	this->body->SetTransform(new_position, NO_ANGLE);
	this->sendPosition();
	delete this->state;
	this->state = new JumpingState(this->body, this);
	this->proxy.sendStateChange(this->id, JUMPING_STATE);
	this->body->SetGravityScale(SI_GRAVEDAD);
	//se setea una pequenia velocidad para que el world lo comience a tener en cuenta para la simulacion
	this->body->SetLinearVelocity(b2Vec2(0, LITTLE_VEL));
}
		
		
		
		
		
		
