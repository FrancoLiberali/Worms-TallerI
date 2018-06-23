#include "turn.h"
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>
#include <algorithm>
#include <arpa/inet.h>
#include <iostream>
#include "proxy.h"
#include <cmath>
#include <stdexcept>
#include "game_finished.h"
#include "query_callback.h"

#define FPS 60.0
#define VELOCITY_IT 8
#define POSITION_IT 3

#define MOVE_TAM 9
#define TURN_LEN 3600
#define MIN_ANGLE_CHANGE 0.09817477
#define THREE_SECONDS 181
#define MAX_POWER 5
#define GUSANO_HEIGHT 0.5
#define GUSANO_WIDTH 0.25
#define MAP_OFFSET 25

Turn::Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<int, std::map<int, Gusano>>& players_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e,
	GameConstants& info_e, MultipleProxy& proxy_e,
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

void Turn::disconnect(int player_id, int active_player, int& turn_actual_len){
	this->players.erase(player_id);
	Proxy& disconnected = this->proxy.erase(player_id);
	disconnected.disconnect();
	this->proxy.sendPlayerDisconnection(player_id);
	if (player_id == active_player){
		turn_actual_len = TURN_LEN;
	}
}

void Turn::gusano_move(char* msj, Gusano& gusano){
	int direction = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	std::cout << "mover gusano\n";
	gusano.move(direction);
}

void Turn::gusano_jump(Gusano& gusano){
	std::cout << "salto\n";
	gusano.jump();
}

void Turn::gusano_back_jump(Gusano& gusano){
	std::cout << "salto\n";
	gusano.backJump();
}

void Turn::take_weapon(int player_id, char* msj){
	int to_take = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	if (!this->fired && this->ammunition[player_id][to_take] != 0){
		this->weapon = to_take;
		this->remote_position = b2Vec2(0, 0);
		this->sight_angle = 0;
		this->regresive_time = 5 * FPS;
		this->power = 1;
		this->proxy.sendTakeWeapon(this->weapon);
	}
}

void Turn::changeSightAngle(char* msj){
	int change = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	if (this->weapon != 0 && this->weapon != 7 && this->weapon != 9 && this->weapon != 10){
		float new_angle = this->sight_angle + change * MIN_ANGLE_CHANGE;
		if (new_angle < (M_PI / 2) && new_angle > -(M_PI / 2)){
			this->sight_angle = new_angle;
			this->proxy.sendChangeSightAngle(change);
		}
	}
}	

void Turn::changeRegresiveTime(char* msj){
	if (this->weapon != 0){
		this->regresive_time = ntohl(*(reinterpret_cast<int*>(msj + 5))) * FPS;
	}
}

void Turn::loadPower(int player_id, Gusano& gusano, int& turn_actual_len){
	if (this->power < MAX_POWER){
		this->power += 0.1;
	}
	if (this->power == MAX_POWER){
		std::cout << "fire automatico\n";
		this->fire(player_id, gusano, turn_actual_len);
	}
}

void Turn::fire(int player_id, Gusano& gusano, int& turn_actual_len){
	if (!this->fired && this->weapon && this->weapon != 9 && this->weapon != 10){
		std::cout << "fire\n";
		b2Vec2 position = gusano.GetPosition();
		int direction = gusano.getDirection();
		this->actual_max_projectile++;
		switch(this->weapon){
			case 1: this->factory.createBazooka(this->actual_max_projectile, position,
												direction, this->sight_angle, this->power);
					break;
			case 2: this->factory.createMorter(this->actual_max_projectile, position,
												direction, this->sight_angle, this->power);
					break;
			case 3: this->factory.createGreenGranade(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case 4: this->factory.createRedGranade(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case 5: this->factory.createBanana(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case 6: this->factory.createSaintGranade(this->actual_max_projectile, position,
										direction, this->sight_angle, this->power, this->regresive_time);
					break;
			case 7: this->factory.createDynamite(this->actual_max_projectile, position,
										direction, this->regresive_time);
					break;
			case 8: this->factory.createBat(gusano, position, direction, this->sight_angle);
					break;
		}
		this->setFired(player_id, turn_actual_len);
	} else if (this->weapon == 9){
		this->fire_air_attack(player_id, turn_actual_len);
	} else if (this->weapon == 10){
		this->teleport(player_id, turn_actual_len, gusano);
	}
}

void Turn::setFired(int player_id, int& turn_actual_len){
	this->ammunition[player_id][this->weapon] -= 1;
	std::cout << "quedan " << this->ammunition[player_id][this->weapon] << "\n";
	if (this->ammunition[player_id][this->weapon] == 0){
		this->proxy.sendFinishedAmunnition(player_id, this->weapon);
	} 
	this->fired = true;
	turn_actual_len = TURN_LEN - THREE_SECONDS;
}

void Turn::changeRemoteObjetive(char* msj){
	this->remote_position = b2Vec2(ntohl(*(reinterpret_cast<int*>(msj + 5))) / 1000, 
								   ntohl(*(reinterpret_cast<int*>(msj + 9))) / 1000);
	this->remote_position.y = -this->remote_position.y;
	std::cout << "cambio a: " << this->remote_position.x << "; " << this->remote_position.y << "\n";
}

void Turn::fire_air_attack(int player_id, int& turn_actual_len){
	float x_to = this->remote_position.x;
	float y_to = this->remote_position.y;
	if (x_to > MAP_OFFSET  &&  x_to < this->info.map_widht + MAP_OFFSET && y_to != 0){
		for (int i = 0; i < this->info.air_attack_cant_missiles; i++){
			this->factory.createAirAttackMissile(this->actual_max_projectile, 
							x_to + this->info.air_attack_missiles_distance * (i - (int) this->info.air_attack_cant_missiles / 2));
			this->actual_max_projectile++;
		}
		this->setFired(player_id, turn_actual_len);
	}
}

void Turn::teleport(int player_id, int& turn_actual_len, Gusano& gusano){
	std::cout << "usando teleporter\n";
	float x_to = this->remote_position.x;
	float y_to = this->remote_position.y;
	if (x_to > MAP_OFFSET  &&  x_to < this->info.map_widht + MAP_OFFSET && y_to != 0){
		//chequea si el lugar donde se quiere poner al gusano no se encuentra ocupado
		QueryCallback callback;
		b2AABB aabb;
		aabb.lowerBound = b2Vec2(x_to - GUSANO_WIDTH, y_to - GUSANO_HEIGHT);
		aabb.upperBound = b2Vec2(x_to + GUSANO_WIDTH, y_to + GUSANO_HEIGHT);
		this->world.QueryAABB(&callback, aabb);
		if (callback.isDesocuped()){
			std::cout << "desocupado\n";
			gusano.teleport(this->remote_position);
			this->setFired(player_id, turn_actual_len);
		}
	}
}

void Turn::play(int active_player, unsigned int active_gusano){
	Gusano& gusano_actual = this->players.at(active_player).at(active_gusano);
	this->proxy.sendTurnBegining(active_player, gusano_actual.getId());
	this->weapon = 0;
	this->fired = false;
	double extra = 0;
	bool keep_simulation = false;
	bool continue_turn = true;
	for (int32 i = 0; i < TURN_LEN || keep_simulation; ++i) { //3600 = 60 segundos = largo del turno
		auto t_start = std::chrono::high_resolution_clock::now();
		
		keep_simulation = false;
		continue_turn = (i < TURN_LEN);
		//interpretacion de todos los mensajes enviados por todos los jugadores
		while(!this->queue.isEmpty()){
			std::cout << "hay evento\n";
			//no es posible generar raise condition porque del otro lado 
			// solo meten asi que si no estaba vacia tampoco lo estara ahora
			char* msj = this->queue.pop();
			int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
			if (msj[0] == 10){
				std::cout << "player a desconectar: " << player_id << "\n";
				this->disconnect(player_id, active_player, i);
				if (this->players.size() == 1){
					delete[] msj;
					throw GameFinished();
				}
			}
			else if (player_id == active_player && continue_turn){
				if (msj[0] == 2){
					this->gusano_move(msj, gusano_actual);
				}
				else if (gusano_actual.isInactive()){
					switch (msj[0]){
						case 3: this->gusano_jump(gusano_actual);
								break;
						case 4: this->gusano_back_jump(gusano_actual);
								break;
						case 5: this->take_weapon(active_player, msj);
								break;
						case 6: this->changeSightAngle(msj);
								break;
						case 7: this->changeRegresiveTime(msj);
								break;
						case 8: this->loadPower(active_player, gusano_actual, i);
								break;
						case 9: this->fire(active_player, gusano_actual, i);
								break;
						case 14: this->changeRemoteObjetive(msj);
								 break;
						
					}
				}
			}
			delete[] msj;
		}
		
		//simulacion
		this->world.Step(1 / float(FPS), VELOCITY_IT, POSITION_IT);
		
		//si el gusano actual sufrio danio duerante la simulacion debe terminar el turno
		if (continue_turn){
			if (gusano_actual.gotDamaged()){
				i = TURN_LEN;
			}
		}

		//process map for projectiles deletion
		// explotaron o se unieron
		std::vector<int>::iterator projectiles_remover_it = this->to_remove_projectiles.begin();
		for (; projectiles_remover_it != this->to_remove_projectiles.end(); ++projectiles_remover_it) {
			std::cout << "hay projectile para destruir\n";
			//remove it from list of projectiles in simulation
			this->projectiles.erase(*projectiles_remover_it);
			//projectile gets deleted because of unique ptr
		}
		this->to_remove_projectiles.clear();
		
		//process map for gusanos deletion
		// murieron o se hundieron
		std::vector<std::pair<int, int>>::iterator gusanos_remover_it = this->to_remove_gusanos.begin();
		for (; gusanos_remover_it != this->to_remove_gusanos.end(); ++gusanos_remover_it) {
			std::cout << "hay gusano para destruir\n";
			//remove it from list of gusanos in simulation
			this->players[gusanos_remover_it->first].erase(gusanos_remover_it->second);
			if (gusanos_remover_it->second == active_gusano){
				i = TURN_LEN;
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
		
		//lista de creacion de proyectiles luego de la explosion de un proyectil fragmentario
		std::vector<FragmentInfo>::iterator c_it = this->to_create.begin();
		for (; c_it != this->to_create.end(); ++c_it) {
			std::cout << "hay projectile para crear\n";
			this->actual_max_projectile++;
			this->factory.createLittleProjectile(this->actual_max_projectile, (*c_it));
		}
		this->to_create.clear();
		
		//cambio en el viento, hace de vez en cuando
		if (i % 1000 == 0){
			/* initialize random seed: */
			srand (time(0));
			/* generate number between -0.1 and 0.1: */
			this->wind += ((rand() % 10) / 50.0) - 0.1;
			std::cout << "wind: " << this->wind << "\n";
		}
		
		// Proyectiles en vuelo actual
		std::map<int, std::unique_ptr<Projectile>>::iterator projectiles_it = this->projectiles.begin();
		for (; projectiles_it != this->projectiles.end(); ++projectiles_it) {
			projectiles_it->second->update(this->wind);
			keep_simulation = true;
		}
		
		std::map<int, std::map<int, Gusano>>::iterator players_it = this->players.begin();
		for (; players_it != this->players.end(); ++players_it) {
			std::map<int, Gusano>::iterator gusanos_it = players_it->second.begin();
			for (; gusanos_it != players_it->second.end(); ++gusanos_it) {
				Gusano& gusano = gusanos_it->second;
				gusano.update();
				//solo se manda informacion sobre los que estan sufriendo algun cambio
				if (!(gusano.isInactive())){
					gusano.sendPosition();
					keep_simulation = true;
				}
			}
		}
		
		auto t_end = std::chrono::high_resolution_clock::now();
		double time_delta = (std::chrono::duration<double, std::micro>(t_end-t_start)).count();
		
		int to_sleep = int(double(1000000/60) - time_delta - extra);
		if (to_sleep >= 0){
			std::this_thread::sleep_for(std::chrono::microseconds(to_sleep));
			extra = 0;
		} else {
			extra = -to_sleep;
		}
	}
	// al final del turno se manda que guarda el arma
	this->proxy.sendTakeWeapon(0);
}
