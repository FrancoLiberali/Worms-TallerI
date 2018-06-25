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

#define RIGHT 1

#define INACTIVE_STATE 0
#define MOVING_STATE 1
#define JUMPING_STATE 2
#define DEAD_STATE 4
#define EXPLOTION_STATE 5
#define MUCHO 3000
#define NO_ANGLE 0

Gusano::Gusano(b2World& world_e, MultipleProxy& proxy_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e, float x, float y, float angle, int life_e) 
		: world(world_e), proxy(proxy_e), to_remove_gusanos(to_remove_gusanos_e),
			user_data(GUSANO_INDICATOR, this), body(world_e, x, y, angle, &user_data), life(life_e){
	
	this->state = new JumpingState(this); //hasta que no haga contacto con el suelo esta saltando
	this->direction = RIGHT;
}

Gusano::Gusano(Gusano&& other) : world(other.world), proxy(other.proxy), to_remove_gusanos(other.to_remove_gusanos),
		user_data(other.user_data), body(std::move(other.body)), state(other.state), direction(other.direction), 
		number(other.number), id(other.id), life(other.life){
	other.state = nullptr;
	this->user_data.pointer = this;
	this->body.setUserData(&(this->user_data));
}

Gusano& Gusano::operator=(Gusano&& other){
	this->user_data = other.user_data;
	this->user_data.pointer = this;
	this->body = std::move(other.body);
	this->state = other.state;
	other.state = nullptr;
	this->life = other.life;
	this->body.setUserData(&(this->user_data));
	
	return *this;
}

Gusano::~Gusano(){
	if (this->state){
		delete this->state;
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
	return this->body.GetPosition();
}

float32 Gusano::GetAngle(){
	return this->body.GetAngle();
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

void Gusano::update(){
	this->damage_suffered = 0;
	try{
		this->state->update(this->GetPosition());
	} catch (const MovingFinished& e){
		delete this->state;
		this->state = new InactiveState();
		this->body.cancelMovement();
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
	} catch (const RotatingFinished& e){
		delete this->state;
		this->state = new InactiveState();
		this->body.cancelMovement();
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
	this->state = new JumpingState(this);
	this->proxy.sendStateChange(this->id, JUMPING_STATE);
	this->body.jump(this->direction);
}

void Gusano::backJump(){
	delete this->state;
	this->state = new JumpingState(this);
	this->proxy.sendStateChange(this->id, JUMPING_STATE);
	this->body.backJump(this->direction);
}

void Gusano::cancelMovement(){
	this->body.cancelMovement();
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
		this->state->update(this->GetPosition());
		delete this->state;
		this->state = new InactiveState();
		this->body.cancelMovement();
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
		this->state = new JumpingState(this);
		this->proxy.sendStateChange(this->id, JUMPING_STATE);
		this->body.setGravity();
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
	this->body.applyExplotion(apply_point, impulse);
	if (!(this->state->isExploted())){
		delete this->state;
		this->state = new ExplotedState(this->body);
		this->proxy.sendStateChange(this->id, EXPLOTION_STATE);
	}
}

void Gusano::teleport(b2Vec2 new_position){
	this->body.teleport(new_position, NO_ANGLE);
	this->sendPosition();
	delete this->state;
	this->state = new JumpingState(this);
	this->proxy.sendStateChange(this->id, JUMPING_STATE);
}
		
		
		
		
		
		
