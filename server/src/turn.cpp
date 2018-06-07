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

#define MOVE_TAM 9
#define TURN_LEN 3600
#define MIN_ANGLE_CHANGE 0.09817477

Turn::Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<int, std::map<int, Gusano*>>& players_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e, GameConstants& info_e, MultipleProxy& proxy_e) :
		world(world_e), queue(queue_e), players(players_e), to_remove_gusanos(to_remove_gusanos_e), info(info_e), 
		proxy(proxy_e), time_step(1.0f / 60.0f), velocity_iterations(8), position_iterations(3){
	//para activar los primeros empiezan contacto
	this->world.Step(this->time_step, this->velocity_iterations, this->position_iterations);
}

Turn::~Turn(){
}

void Turn::gusano_move(char* msj, int active_player, int active_gusano){
	int direction = ntohl(*(reinterpret_cast<int*>(msj + 5)));
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		std::cout << "mover gusano\n";
		gusano->move(direction);
	}
}

void Turn::gusano_jump(char* msj, int active_player, int active_gusano){
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		std::cout << "salto\n";
		gusano->jump();
	}
}

void Turn::gusano_back_jump(char* msj, int active_player, int active_gusano){
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		std::cout << "salto\n";
		gusano->backJump();
	}
}

void Turn::take_weapon(char* msj, int active_player, int active_gusano){
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		this->weapon = ntohl(*(reinterpret_cast<int*>(msj + 5)));
		this->sight_angle = 0;
		this->regresive_time = 5;
		this->power = 0;
		this->proxy.sendTakeWeapon(this->weapon);
	}
}

void Turn::changeSightAngle(char* msj, int active_player, int active_gusano){
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		int change = ntohl(*(reinterpret_cast<int*>(msj + 5)));
		if (this->weapon != 0 && this->weapon != 7 && this->weapon != 9 && this->weapon != 10){
			this->sight_angle += change * MIN_ANGLE_CHANGE;
			this->proxy.sendChangeSightAngle(change);
		}
	}
}	

void Turn::changeRegresiveTime(char* msj, int active_player, int active_gusano){
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		if (this->weapon != 0){
			this->regresive_time = ntohl(*(reinterpret_cast<int*>(msj + 5)));
		}
	}
}

void Turn::loadPower(int active_player, int active_gusano){
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		this->power += 1;
	}
}

void Turn::fire(int active_player, int active_gusano){
	Gusano* gusano = this->players[active_player][active_gusano];
	if (gusano->isInactive()){
		std::cout << "fire\n";
		switch(this->weapon){
			case 0: break;
			case 1: this->fire_bazooka(gusano);
					break;
			case 2: this->fire_morter(gusano);
					break;
		}
	}
}

void Turn::fire_bazooka(Gusano* gusano){
	b2Vec2 position = gusano->GetPosition();
	this->actual_max_projectile++;
	Bazooka* bazooka = new Bazooka(this->world, this->actual_max_projectile, position.x, 
						position.y, this->sight_angle, this->power, this->info, 
						this->to_remove_projectiles, this->proxy);
	this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, bazooka));
}

void Turn::fire_morter(Gusano* gusano){
	b2Vec2 position = gusano->GetPosition();
	this->actual_max_projectile++;
	Morter* morter = new Morter(this->world, this->actual_max_projectile, position.x, 
						position.y, this->sight_angle, this->power, this->info, 
						this->to_remove_projectiles, this->to_create, this->proxy);
	this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, morter));
}

void Turn::play(int active_player, unsigned int active_gusano){
	this->proxy.sendTurnBegining(active_player, active_gusano);
	this->weapon = 0;
	double extra = 0;
	for (int32 i = 0; i < TURN_LEN; ++i) { //3600 = 60 segundos = largo del turno
		auto t_start = std::chrono::high_resolution_clock::now();
		
		while(!this->queue.isEmpty()){
			std::cout << "hay evento\n";
			//no es posible generar raise condition porque del otro lado solo meten asi que si no estaba vacia tampoco lo estara ahora
			char* msj = this->queue.front();
			this->queue.pop();
			int player_id = ntohl(*(reinterpret_cast<int*>(msj + 1)));
			if (player_id == active_player){
				switch (msj[0]){
					case 1: this->gusano_move(msj, active_player, active_gusano);
							delete[] msj;
							break;
					case 2: this->gusano_jump(msj, active_player, active_gusano);
							delete[] msj;
							break;
					case 3: this->gusano_back_jump(msj, active_player, active_gusano);
							delete[] msj;
							break;
					case 4: this->take_weapon(msj, active_player, active_gusano);
							delete[] msj;
							break;
					case 5: this->changeSightAngle(msj, active_player, active_gusano);
							delete[] msj;
							break;
					case 6: this->changeRegresiveTime(msj, active_player, active_gusano);
							delete[] msj;
							break;
					case 7: this->loadPower(active_player, active_gusano);
							delete[] msj;
							break;
					case 8: this->fire(active_player, active_gusano);
							delete[] msj;
							break;
				}
			}
		}
		
		this->world.Step(this->time_step, this->velocity_iterations, this->position_iterations);
		
		//process map for projectiles deletion
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
		
		std::vector<FragmentInfo*>::iterator c_it = this->to_create.begin();
		for (; c_it != this->to_create.end(); ++c_it) {
			std::cout << "hay projectile para crear\n";
			this->actual_max_projectile++;
			LittleProjectile* little = new LittleProjectile(this->world, this->actual_max_projectile, (*c_it)->x,
			(*c_it)->y, (*c_it)->angle, (*c_it)->vel, (*c_it)->damage, (*c_it)->radius, this->to_remove_projectiles, this->proxy);
			this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, little));
			delete (*c_it);
		}
		this->to_create.clear();
		
		std::map<int, Projectile*>::iterator projectiles_it = this->projectiles.begin();
		for (; projectiles_it != this->projectiles.end(); ++projectiles_it) {
			projectiles_it->second->update(0);
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
