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

#define MOVE_TAM 9
#define TURN_LEN 3600

Turn::Turn(b2World& world_e, ProtectedQueue& queue_e, std::map<unsigned int, Gusano*>& gusanos_e, 
	std::map<unsigned int, Gusano*>& to_remove_gusanos_e, GameConstants& info_e) :
		world(world_e), queue(queue_e), gusanos(gusanos_e), to_remove_gusanos(to_remove_gusanos_e), info(info_e), 
		time_step(1.0f / 60.0f), velocity_iterations(8), position_iterations(3){
	//para activar los primeros empiezan contacto
	this->world.Step(this->time_step, this->velocity_iterations, this->position_iterations);
}

Turn::~Turn(){
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
				case 1: { unsigned int gusano_number = ntohl(*(reinterpret_cast<unsigned int*>(msj + 1)));
						if (gusano_number == active_number){
							int direction = ntohl(*(reinterpret_cast<int*>(msj + 5)));
							Gusano* gusano = this->gusanos.at(gusano_number);
							if (gusano->isInactive()){
								std::cout << "mover gusano\n";
								gusano->move(direction);
							}
						}
						delete[] msj;
						break;
						}
				case 2: { unsigned int gusano_number = ntohl(*(reinterpret_cast<unsigned int*>(msj + 1)));
						if (gusano_number == active_number){
							Gusano* gusano = this->gusanos.at(gusano_number);
							if (gusano->isInactive()){
								std::cout << "salto\n";
								gusano->jump();
							}
						}
						delete[] msj;
						break;
						}
			}
		}
		
		this->world.Step(this->time_step, this->velocity_iterations, this->position_iterations);
		
		//process list for deletion
		std::vector<Projectile*>::iterator it = this->to_remove.begin();
		for (; it != this->to_remove.end(); ++it) {
			std::cout << "hay algo para destruir\n";
			Projectile* exploted_projectile = *it;
			//remove it from list of projectiles in simulation
			std::vector<Projectile*>::iterator it2 = std::find(this->projectiles.begin(), this->projectiles.end(), exploted_projectile);
			if (it2 != this->projectiles.end()){
				this->projectiles.erase(it2);
			}
			delete exploted_projectile;
		}
		this->to_remove.clear();
		
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
			std::cout << "termina detruir\n";
		}
		this->to_remove_gusanos.clear();
		
		std::vector<LittleProjectile*>::iterator it2 = this->to_create.begin();
		for (; it2 != this->to_create.end(); ++it2) {
			std::cout << "hay algo para crear\n";
			LittleProjectile* little = *it2;
			little->create();
			this->projectiles.push_back((Projectile*)little);
		}
		this->to_create.clear();
		
		std::vector<Projectile*>::iterator it3 = this->projectiles.begin();
		for (int j = 0; it3 != this->projectiles.end(); ++it3, j++) {
			(*it3)->update();
			//en lugar de printearlo se deberia mandar al client
			//ver si el client va a mostrar solo los que yo le mande o tambien le tendria que avisar cuando explotan
			std::cout << "projectile " << j << ": " << (*it3)->GetPosition().x << "; " << (*it3)->GetPosition().y << "\n";
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
