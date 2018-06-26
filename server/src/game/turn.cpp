#include "game/turn.h"
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>
#include <algorithm>
#include <arpa/inet.h>
#include <iostream>
#include "server/proxy.h"
#include <cmath>
#include <stdexcept>
#include "game/game_finished.h"
#include "game/Box2d_elements/query_callback.h"

#define FPS 60
#define VELOCITY_IT 8
#define POSITION_IT 3
#define TURN_LEN 3600  //3600 = 60 segundos = largo del turno

#define EVENT 0
#define MOVE 2
#define JUMP 3
#define BACK_JUMP 4
#define WEAPON 5
#define ANGLE 6
#define TIME 7
#define POWER 8
#define FIRE 9
#define DISCONNECTION 10
#define OBJETIVE 14

#define NO_WEAPON 0
#define BAZOOKA 1
#define MORTER 2
#define GREEN_GRANADE 3
#define RED_GRANADE 4
#define BANANA 5
#define SAINT_GRANADE 6
#define DYNAMITE 7
#define BAT 8
#define AIR_ATTACK 9
#define TELEPORT 10

#define MIN_ANGLE_CHANGE 0.09817477 // 5.625 grados, la diferencia que tiene el client entre los angulos del sprite
#define THREE_SECONDS 181
#define TO_MICROSECONDS 1000000
#define DEFAULT_POWER 1
#define DEFAULT_TIME 5
#define DEFAULT_ANGLE 0
#define DEFAULT_REMOTE_X 0
#define DEFAULT_REMOTE_Y 0
#define MAX_POWER 5
#define MIN_POWER_CHANGE 0.1
#define TO_METERS 1000
#define GUSANO_HEIGHT 0.5
#define GUSANO_WIDTH 0.25
#define MAP_OFFSET 25

#define BETWEEN_TURNS_SLEEP 2

Turn::Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<int, std::map<int, Gusano>>& players_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e,
	const GameConstants& info_e, MultipleProxy& proxy_e,
	ObjectsFactory& factory_e) :
		world(world_e), queue(queue_e), players(players_e), to_remove_gusanos(to_remove_gusanos_e),
		info(info_e), proxy(proxy_e), factory(factory_e){
	std::map<int, std::map<int, Gusano>>::iterator players_it = this->players.begin();
	for (; players_it != this->players.end(); ++players_it){
		this->ammunition.insert(std::pair<int, std::vector<int>>(players_it->first, this->info.ammunition));
	}
	this->factory.addTurnInfo(&(this->projectiles), &(this->to_remove_projectiles), &(this->to_create));
}

Turn::~Turn(){
}

void Turn::play(int active_player, unsigned int active_gusano){
	Gusano& gusano_actual = this->players.at(active_player).at(active_gusano);
	this->proxy.sendTurnBegining(active_player, gusano_actual.getId());
	
	// seteando todas las variables de inicio de turno
	this->weapon = NO_WEAPON; //el gusano empieza sin arma
	this->fired = false; //no se ha disparado
	double extra = 0; //no se debe tiempo de frames anterior
	bool something_to_simulate = false; //no hay proyectil ni gusano en movimiento
	bool continue_turn = true; //todavia queda tiempo en el turno
	for (int32 i = 0; i < TURN_LEN || something_to_simulate; ++i) {
		auto t_start = std::chrono::high_resolution_clock::now();
		
		// se dice que no hay nada para simular antes de verificar como quedaron las listas de gusanos y proyectiles
		something_to_simulate = false;
		continue_turn = (i < TURN_LEN);
		
		this->interpretMessages(active_player, gusano_actual, continue_turn, i);
		
		//simulacion
		this->world.Step(1 / float(FPS), VELOCITY_IT, POSITION_IT);
		
		//si el gusano actual sufrio danio duerante la simulacion debe terminar el turno
		if (continue_turn){
			if (gusano_actual.gotDamaged()){
				i = TURN_LEN;
			}
		}
		
		this->processProjectilesDeletion();
		
		this->processGusanosDeletion(active_gusano, i);
		
		this->processProjectilesCreation();
		
		this->processWindChange(i);
		
		this->processProjectilesInFlight(something_to_simulate);
		
		this->processAliveGusanos(something_to_simulate);
		
		//es un segundo
		if (i % FPS == 0 && continue_turn){
			this->proxy.sendSecond();
		}
		
		auto t_end = std::chrono::high_resolution_clock::now();
		double time_delta = (std::chrono::duration<double, std::micro>(t_end-t_start)).count();
		
		int to_sleep = int(double(TO_MICROSECONDS / (float) FPS) - time_delta - extra);
		if (to_sleep >= 0){
			std::this_thread::sleep_for(std::chrono::microseconds(to_sleep));
			extra = 0;
		} else {
			extra = -to_sleep;
		}
	}
	// al final del turno se manda que guarda el arma
	this->proxy.sendTakeWeapon(NO_WEAPON);
	std::this_thread::sleep_for(std::chrono::seconds(BETWEEN_TURNS_SLEEP));
}

void Turn::interpretMessages(int active_player,Gusano& gusano_actual, bool& continue_turn, int& turn_actual_len){
	while(!this->queue.isEmpty()){
		//no es posible generar raise condition porque del otro lado 
		// solo meten asi que si no estaba vacia tampoco lo estara ahora
		char* msj = this->queue.pop();
		int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
		if (msj[EVENT] == DISCONNECTION){
			this->disconnect(player_id, active_player, turn_actual_len);
			if (this->players.size() == 1){
				delete[] msj;
				throw GameFinished();
			}
		} else if (player_id == active_player && continue_turn){
			if (msj[EVENT] == MOVE){
				this->gusanoMove(msj, gusano_actual);
			} else if (gusano_actual.isInactive()){
				switch (msj[EVENT]){
					case JUMP: gusano_actual.jump();
							break;
					case BACK_JUMP: gusano_actual.backJump();
							break;
					case WEAPON: this->takeWeapon(active_player, msj);
							break;
					case ANGLE: this->changeSightAngle(msj);
							break;
					case TIME: this->changeRegresiveTime(msj);
							break;
					case POWER: this->loadPower(active_player, gusano_actual, turn_actual_len);
							break;
					case FIRE: this->fire(active_player, gusano_actual, turn_actual_len);
							break;
					case OBJETIVE: this->changeRemoteObjetive(msj);
							 break;
					
				}
			}
		}
		delete[] msj;
	}
}



void Turn::disconnect(int player_id, int active_player, int& turn_actual_len){
	this->players.erase(player_id);
	Proxy& disconnected = this->proxy.erase(player_id);
	disconnected.disconnect();
	this->proxy.sendPlayerDisconnection(player_id);
	if (player_id == active_player){
		turn_actual_len = TURN_LEN;
	}
}

void Turn::gusanoMove(char* msj, Gusano& gusano){
	int direction = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	gusano.move(direction);
}

void Turn::takeWeapon(int player_id, char* msj){
	int to_take = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	if (!this->fired && this->ammunition[player_id][to_take] != 0){
		this->weapon = to_take;
		this->remote_position = b2Vec2(DEFAULT_REMOTE_X, DEFAULT_REMOTE_Y);
		this->sight_angle = DEFAULT_ANGLE;
		this->regresive_time = DEFAULT_TIME * FPS;
		this->power = DEFAULT_POWER;
		this->proxy.sendTakeWeapon(this->weapon);
	}
}

void Turn::changeSightAngle(char* msj){
	int change = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	if (this->weapon != NO_WEAPON && this->weapon != DYNAMITE && this->weapon != AIR_ATTACK && this->weapon != TELEPORT){
		float new_angle = this->sight_angle + change * MIN_ANGLE_CHANGE;
		if (new_angle < (M_PI / 2) && new_angle > -(M_PI / 2)){
			this->sight_angle = new_angle;
			this->proxy.sendChangeSightAngle(change);
		}
	}
}	

void Turn::changeRegresiveTime(char* msj){
	if (this->weapon != NO_WEAPON){
		this->regresive_time = ntohl(*(reinterpret_cast<int*>(msj + 5))) * FPS;
	}
}

void Turn::loadPower(int player_id, Gusano& gusano, int& turn_actual_len){
	if (this->power < MAX_POWER){
		this->power += MIN_POWER_CHANGE;
	} else {
		this->fire(player_id, gusano, turn_actual_len);
	}
}

void Turn::fire(int player_id, Gusano& gusano, int& turn_actual_len){
	if (!this->fired && this->weapon && this->weapon != AIR_ATTACK && this->weapon != TELEPORT){
		b2Vec2 position = gusano.GetPosition();
		int direction = gusano.getDirection();
		this->actual_max_projectile++;
		switch(this->weapon){
			case BAZOOKA: this->factory.createBazooka(this->actual_max_projectile, position,
												direction, this->sight_angle, this->power);
					break;
			case MORTER: this->factory.createMorter(this->actual_max_projectile, position,
												direction, this->sight_angle, this->power);
					break;
			case GREEN_GRANADE: this->factory.createGreenGranade(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case RED_GRANADE: this->factory.createRedGranade(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case BANANA: this->factory.createBanana(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case SAINT_GRANADE: this->factory.createSaintGranade(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case DYNAMITE: this->factory.createDynamite(this->actual_max_projectile, position,
										direction, this->regresive_time);
					break;
			case BAT: this->factory.createBat(gusano, position, direction, this->sight_angle);
					break;
		}
		this->setFired(player_id, turn_actual_len);
	} else if (this->weapon == AIR_ATTACK){
		this->fireAirAttack(player_id, turn_actual_len);
	} else if (this->weapon == TELEPORT){
		this->teleport(player_id, turn_actual_len, gusano);
	}
}

void Turn::setFired(int player_id, int& turn_actual_len){
	this->ammunition[player_id][this->weapon] -= 1;
	if (this->ammunition[player_id][this->weapon] == 0){
		this->proxy.sendFinishedAmunnition(player_id, this->weapon);
	} 
	this->fired = true;
	turn_actual_len = TURN_LEN - THREE_SECONDS;
}

void Turn::changeRemoteObjetive(char* msj){
	this->remote_position = b2Vec2(ntohl(*(reinterpret_cast<int*>(msj + 5))) / TO_METERS, 
								   ntohl(*(reinterpret_cast<int*>(msj + 9))) / TO_METERS);
	this->remote_position.y = -this->remote_position.y;
}

void Turn::fireAirAttack(int player_id, int& turn_actual_len){
	float x_to = this->remote_position.x;
	float y_to = this->remote_position.y;
	if (x_to > MAP_OFFSET  &&  x_to < this->info.map_widht + MAP_OFFSET && y_to != DEFAULT_REMOTE_Y){
		for (int i = 0; i < this->info.air_attack_cant_missiles; i++){
			this->factory.createAirAttackMissile(this->actual_max_projectile, 
							x_to + this->info.air_attack_missiles_distance * (i - (int) this->info.air_attack_cant_missiles / 2));
			this->actual_max_projectile++;
		}
		this->setFired(player_id, turn_actual_len);
		this->proxy.sendRemoteWork(AIR_ATTACK);
	}
}

void Turn::teleport(int player_id, int& turn_actual_len, Gusano& gusano){
	float x_to = this->remote_position.x;
	float y_to = this->remote_position.y;
	if (x_to > MAP_OFFSET  &&  x_to < this->info.map_widht + MAP_OFFSET && y_to != DEFAULT_REMOTE_Y){
		//chequea si el lugar donde se quiere poner al gusano no se encuentra ocupado
		QueryCallback callback;
		b2AABB aabb;
		aabb.lowerBound = b2Vec2(x_to - GUSANO_WIDTH, y_to - GUSANO_HEIGHT);
		aabb.upperBound = b2Vec2(x_to + GUSANO_WIDTH, y_to + GUSANO_HEIGHT);
		this->world.QueryAABB(&callback, aabb);
		if (callback.isDesocuped()){
			gusano.teleport(this->remote_position);
			this->setFired(player_id, turn_actual_len);
			this->proxy.sendRemoteWork(TELEPORT);
		}
	}
}

void Turn::processProjectilesDeletion(){
	std::vector<int>::iterator projectiles_remover_it = this->to_remove_projectiles.begin();
	for (; projectiles_remover_it != this->to_remove_projectiles.end(); ++projectiles_remover_it) {
		//remove it from list of projectiles in simulation
		this->projectiles.erase(*projectiles_remover_it);
		//projectile gets deleted because of unique ptr
	}
	this->to_remove_projectiles.clear();
}

void Turn::processGusanosDeletion(int active_gusano, int& turn_actual_len){
	std::vector<std::pair<int, int>>::iterator gusanos_remover_it = this->to_remove_gusanos.begin();
	for (; gusanos_remover_it != this->to_remove_gusanos.end(); ++gusanos_remover_it) {
		//remove it from list of gusanos in simulation
		this->players[gusanos_remover_it->first].erase(gusanos_remover_it->second);
		if (gusanos_remover_it->second == active_gusano){
			turn_actual_len = TURN_LEN;
		}
		if (this->players[gusanos_remover_it->first].size() == 0){
			this->proxy.sendPlayerLoose(gusanos_remover_it->first);
			this->players.erase(gusanos_remover_it->first);
			if (this->players.size() == 1){
				throw GameFinished();
			}
		}
	}
	this->to_remove_gusanos.clear();
}

void Turn::processProjectilesCreation(){
	std::vector<FragmentInfo>::iterator c_it = this->to_create.begin();
	for (; c_it != this->to_create.end(); ++c_it) {
		this->actual_max_projectile++;
		this->factory.createLittleProjectile(this->actual_max_projectile, (*c_it));
	}
	this->to_create.clear();
}

#define WIND_CHANGE_TIME 1000
#define BETWEEN_0_AND_9 10
#define BETWEEN_0_AND_0d18 50.0
#define BETWEEN_m0d05_AND_0d13 0.05
#define BETWEEN_m0d13_AND_0d05 0.13
#define BETWEEN_m0d09_AND_0d09 0.09

void Turn::processWindChange(int turn_actual_len){
	if (turn_actual_len % WIND_CHANGE_TIME == 0 && this->projectiles.size() == 0){
		/* initialize random seed: */
		srand (time(0));
		if (this->wind < 0){
			/* generate number between -0.05 and 0.11: */
			this->wind += ((rand() % BETWEEN_0_AND_9) / BETWEEN_0_AND_0d18) - BETWEEN_m0d05_AND_0d13;
		} else if (this->wind > 0){
			/* generate number between -0.11 and 0.05: */
			this->wind += ((rand() % BETWEEN_0_AND_9) / BETWEEN_0_AND_0d18) - BETWEEN_m0d13_AND_0d05;
		} else {
			/* generate number between -0.08 and 0.08: */
			this->wind += ((rand() % BETWEEN_0_AND_9) / BETWEEN_0_AND_0d18) - BETWEEN_m0d09_AND_0d09;
		}
		this->proxy.sendWindChange(this->wind);
	}
}

void Turn::processProjectilesInFlight(bool& something_to_simulate){
	std::map<int, std::unique_ptr<Projectile>>::iterator projectiles_it = this->projectiles.begin();
	for (; projectiles_it != this->projectiles.end(); ++projectiles_it) {
		projectiles_it->second->update(this->wind);
		something_to_simulate = true;
	}
}

void Turn::processAliveGusanos(bool& something_to_simulate){
	std::map<int, std::map<int, Gusano>>::iterator players_it = this->players.begin();
	for (; players_it != this->players.end(); ++players_it) {
		std::map<int, Gusano>::iterator gusanos_it = players_it->second.begin();
		for (; gusanos_it != players_it->second.end(); ++gusanos_it) {
			Gusano& gusano = gusanos_it->second;
			gusano.update();
			//solo se manda informacion sobre los que estan sufriendo algun cambio
			if (!(gusano.isInactive())){
				gusano.sendPosition();
				something_to_simulate = true;
			}
		}
	}
}
