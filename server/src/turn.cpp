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

Turn::Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<unsigned int, Gusano*>& gusanos_e, 
	std::map<unsigned int, Gusano*>& to_remove_gusanos_e, GameConstants& info_e, MokProxy& proxy_e) :
		world(world_e), queue(queue_e), gusanos(gusanos_e), to_remove_gusanos(to_remove_gusanos_e), info(info_e), 
		proxy(proxy_e), time_step(1.0f / 60.0f), velocity_iterations(8), position_iterations(3){
	//para activar los primeros empiezan contacto
	this->world.Step(this->time_step, this->velocity_iterations, this->position_iterations);
}

Turn::~Turn(){
}

void Turn::gusano_move(char* msj, int active_number){
	unsigned int gusano_number = ntohl(*(reinterpret_cast<unsigned int*>(msj + 1)));
	if (gusano_number == active_number){
		int direction = ntohl(*(reinterpret_cast<int*>(msj + 5)));
		Gusano* gusano = this->gusanos.at(gusano_number);
		if (gusano->isInactive()){
			std::cout << "mover gusano\n";
			gusano->move(direction);
		}
	}
}

void Turn::gusano_jump(char* msj, int active_number){
	unsigned int gusano_number = ntohl(*(reinterpret_cast<unsigned int*>(msj + 1)));
	if (gusano_number == active_number){
		Gusano* gusano = this->gusanos.at(gusano_number);
		if (gusano->isInactive()){
			std::cout << "salto\n";
			gusano->jump();
		}
	}
}

void Turn::fire_weapon_sight_power(char* msj, int active_number){
	unsigned int gusano_number = ntohl(*(reinterpret_cast<unsigned int*>(msj + 1)));
	if (gusano_number == active_number){
		int weapon = ntohl(*(reinterpret_cast<int*>(msj + 5)));
		int sight_angle = ntohl(*(reinterpret_cast<int*>(msj + 9)));
		int power = ntohl(*(reinterpret_cast<int*>(msj + 13)));
		Gusano* gusano = this->gusanos.at(gusano_number);
		if (gusano->isInactive()){
			std::cout << "fire\n";
			switch(weapon){
				case 0: this->fire_bazooka(msj, gusano, sight_angle, power);
						break;
				case 1: this->fire_morter(msj, gusano, sight_angle, power);
						break;
			}
		}
	}
}

void Turn::fire_bazooka(char* msj, Gusano* gusano, int sight_angle, int power){
	b2Vec2 position = gusano->GetPosition();
	this->actual_max_projectile++;
	Bazooka* bazooka = new Bazooka(this->world, this->actual_max_projectile, position.x, 
						position.y, sight_angle, power, this->info, 
						this->to_remove_projectiles, this->proxy);
	this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, bazooka));
}

void Turn::fire_morter(char* msj, Gusano* gusano, int sight_angle, int power){
	b2Vec2 position = gusano->GetPosition();
	this->actual_max_projectile++;
	Morter* morter = new Morter(this->world, this->actual_max_projectile, position.x, 
						position.y, sight_angle, power, this->info, 
						this->to_remove_projectiles, this->to_create, this->proxy);
	this->projectiles.insert(std::pair<int, Projectile*>(this->actual_max_projectile, morter));
}

void Turn::play(unsigned int active_number){
	double extra = 0;
	for (int32 i = 0; i < TURN_LEN; ++i) { //3600 = 60 segundos = largo del turno
		auto t_start = std::chrono::high_resolution_clock::now();
		
		while(!this->queue.isEmpty()){
			std::cout << "hay evento\n";
			//no es posible generar raise condition porque del otro lado solo meten asi que si no estaba vacia tampoco lo estara ahora
			char* msj = this->queue.front();
			this->queue.pop();
			switch (msj[0]){
				case 1: this->gusano_move(msj, active_number);
						delete[] msj;
						break;
				case 2: this->gusano_jump(msj, active_number);
						delete[] msj;
						break;
				case 3: this->fire_weapon_sight_power(msj, active_number);
						delete[] msj;
						break;
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
		std::map<unsigned int, Gusano*>::iterator gusanos_remover_it = this->to_remove_gusanos.begin();
		for (; gusanos_remover_it != this->to_remove_gusanos.end(); ++gusanos_remover_it) {
			std::cout << "hay gusano para destruir\n";
			unsigned int dead_number = gusanos_remover_it->first;
			Gusano* dead_gusano = gusanos_remover_it->second;
			//remove it from list of gusanos in simulation
			this->gusanos.erase(dead_number);
			delete dead_gusano;
			if (this->gusanos.size() == 0){
				i = TURN_LEN;
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
			projectiles_it->second->update();
			//en lugar de printearlo se deberia mandar al client
			//ver si el client va a mostrar solo los que yo le mande o tambien le tendria que avisar cuando explotan
			std::cout << "projectile " << projectiles_it->first << ": " << projectiles_it->second->GetPosition().x << "; " << projectiles_it->second->GetPosition().y << "\n";
		}
		std::map<unsigned int, Gusano*>::iterator gusanos_it = this->gusanos.begin();
		for (; gusanos_it != this->gusanos.end(); ++gusanos_it) {
			gusanos_it->second->update();
			//solo se manda informacion sobre los que estan sufriendo algun cambio
			if (!(gusanos_it->second->isInactive())){
				gusanos_it->second->sendPosition();
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
