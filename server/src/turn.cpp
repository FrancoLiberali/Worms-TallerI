#include "turn.h"
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>
#include <algorithm>
#include <arpa/inet.h>
#include <iostream>
#include "proxy.h"
#include "fake_proxy/mok_proxy.h"
#include "bazooka.h"
#include "morter.h"
#include <cmath>
#include <stdexcept>

#define MOVE_TAM 9
#define TURN_LEN 3600
#define MIN_ANGLE_CHANGE 0.09817477
#define THREE_SECONDS 181
#define MAX_POWER 5

Turn::Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<int, std::map<int, Gusano*>>& players_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e, GameConstants& info_e, MultipleProxy& proxy_e) :
		world(world_e), queue(queue_e), players(players_e), to_remove_gusanos(to_remove_gusanos_e), info(info_e), 
		proxy(proxy_e), time_step(1.0f / 60.0f), velocity_iterations(8), position_iterations(3){
	
}

Turn::~Turn(){
}

void Turn::disconnect(int player_id, int active_player, int& turn_actual_len){
	std::map<int, Gusano*>::iterator gusanos_it = players[player_id].begin();
	for (; gusanos_it != players[player_id].end(); ++gusanos_it) {
		Gusano* gusano = gusanos_it->second;
		delete gusano;
	}
	this->players.erase(player_id);
	this->proxy.erase(player_id);
	this->proxy.sendPlayerDisconnection(player_id);
	if (player_id == active_player){
		turn_actual_len = TURN_LEN;
	}
}

void Turn::gusano_move(char* msj, Gusano* gusano){
	int direction = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	std::cout << "mover gusano\n";
	gusano->move(direction);
}

void Turn::gusano_jump(char* msj, Gusano* gusano){
	std::cout << "salto\n";
	gusano->jump();
}

void Turn::gusano_back_jump(char* msj, Gusano* gusano){
	std::cout << "salto\n";
	gusano->backJump();
}

void Turn::take_weapon(char* msj){
	int to_take = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	if (!this->fired && *(this->info.ammunition[to_take]) != 0){
		this->weapon = to_take; 
		this->sight_angle = 0;
		this->regresive_time = 5;
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
		this->regresive_time = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	}
}

void Turn::loadPower(Gusano* gusano, int& turn_actual_len){
	if (this->power < MAX_POWER){
		this->power += 0.1;
	}
	if (this->power == MAX_POWER){
		this->fire(gusano, turn_actual_len);
	}
}

void Turn::fire(Gusano* gusano, int& turn_actual_len){
	if (!this->fired && this->weapon){
		std::cout << "fire\n";
		b2Vec2 position = gusano->GetPosition();
		int direction = gusano->getDirection();
		this->actual_max_projectile++;
		switch(this->weapon){
			case 1: this->fire_bazooka(gusano, position, direction);
					break;
			case 2: this->fire_morter(gusano, position, direction);
					break;
		}
		*(this->info.ammunition[this->weapon]) -= 1;
		std::cout << "quedan " << *(this->info.ammunition[this->weapon]) << "\n";
		this->fired = true;
		turn_actual_len = TURN_LEN - THREE_SECONDS;
	}
}

void Turn::fire_bazooka(Gusano* gusano, b2Vec2 position, int direction){
	Bazooka* bazooka = new Bazooka(this->world, this->actual_max_projectile, position.x, 
						position.y, direction, this->sight_angle, this->power, this->info, 
						this->to_remove_projectiles, this->proxy);
	this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, bazooka));
}

void Turn::fire_morter(Gusano* gusano, b2Vec2 position, int direction){
	Morter* morter = new Morter(this->world, this->actual_max_projectile, position.x, 
						position.y, direction, this->sight_angle, this->power, this->info, 
						this->to_remove_projectiles, this->to_create, this->proxy);
	this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, morter));
}

void Turn::play(int active_player, unsigned int active_gusano){
	this->proxy.sendTurnBegining(active_player, this->players[active_player][active_gusano]->getId());
	this->weapon = 0;
	this->proxy.sendTakeWeapon(this->weapon);
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
			char* msj = this->queue.front();
			this->queue.pop();
			int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
			Gusano* gusano = this->players[active_player][active_gusano];
			if (msj[0] == 1){
				this->disconnect(player_id, active_player, i);
			}
			else if (player_id == active_player && continue_turn && gusano->isInactive()){
				switch (msj[0]){
					case 2: this->gusano_move(msj, gusano);
							break;
					case 3: this->gusano_jump(msj, gusano);
							break;
					case 4: this->gusano_back_jump(msj, gusano);
							break;
					case 5: this->take_weapon(msj);
							break;
					case 6: this->changeSightAngle(msj);
							break;
					case 7: this->changeRegresiveTime(msj);
							break;
					case 8: this->loadPower(gusano, i);
							break;
					case 9: this->fire(gusano, i);
							break;
				}
			}
			delete[] msj;
		}
		
		//simulacion
		this->world.Step(this->time_step, this->velocity_iterations, this->position_iterations);
		
		//si el gusano actual sufrio danio duerante la simulacion debe terminar el turno
		try{
			if (this->players.at(active_player).at(active_gusano)->gotDamaged()){
				i = TURN_LEN;
			}
		} catch (std::out_of_range& e){
		}

		//process map for projectiles deletion
		// explotaron o se unieron
		std::map<int, Projectile*>::iterator projectiles_remover_it = this->to_remove_projectiles.begin();
		for (; projectiles_remover_it != this->to_remove_projectiles.end(); ++projectiles_remover_it) {
			std::cout << "hay projectile para destruir\n";
			int to_remove_number = projectiles_remover_it->first;
			Projectile* remove_projectile = projectiles_remover_it->second;
			//remove it from list of projectiles in simulation
			this->projectiles.erase(to_remove_number);
			delete remove_projectile;
		}
		this->to_remove_projectiles.clear();
		
		//process map for gusanos deletion
		// murieron o se hundieron
		std::vector<std::pair<int, int>>::iterator gusanos_remover_it = this->to_remove_gusanos.begin();
		for (; gusanos_remover_it != this->to_remove_gusanos.end(); ++gusanos_remover_it) {
			std::cout << "hay gusano para destruir\n";
			Gusano* dead_gusano = this->players[gusanos_remover_it->first][gusanos_remover_it->second];
			//remove it from list of gusanos in simulation
			this->players[gusanos_remover_it->first].erase(gusanos_remover_it->second);
			delete dead_gusano;
			if (this->players[gusanos_remover_it->first].size() == 0){
				this->players.erase(gusanos_remover_it->first);
			}
		}
		this->to_remove_gusanos.clear();
		
		//lista de creacion de proyectiles luego de la explosion de un proyectil fragmentario
		std::vector<FragmentInfo*>::iterator c_it = this->to_create.begin();
		for (; c_it != this->to_create.end(); ++c_it) {
			std::cout << "hay projectile para crear\n";
			this->actual_max_projectile++;
			LittleProjectile* little = new LittleProjectile(this->world, this->actual_max_projectile, (*c_it)->x,
			(*c_it)->y, (*c_it)->direction, (*c_it)->angle, (*c_it)->vel, (*c_it)->damage, (*c_it)->radius, this->to_remove_projectiles, this->proxy);
			this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, little));
			delete (*c_it);
		}
		this->to_create.clear();
		
		// Proyectiles en vuelo actual
		std::map<int, Projectile*>::iterator projectiles_it = this->projectiles.begin();
		for (; projectiles_it != this->projectiles.end(); ++projectiles_it) {
			projectiles_it->second->update();
			keep_simulation = true;
		}
		
		std::map<int, std::map<int, Gusano*>>::iterator players_it = this->players.begin();
		for (; players_it != this->players.end(); ++players_it) {
			std::map<int, Gusano*>::iterator gusanos_it = players_it->second.begin();
			for (; gusanos_it != players_it->second.end(); ++gusanos_it) {
				Gusano* gusano = gusanos_it->second;
				gusano->update();
				//solo se manda informacion sobre los que estan sufriendo algun cambio
				if (!(gusano->isInactive())){
					gusano->sendPosition();
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
}
