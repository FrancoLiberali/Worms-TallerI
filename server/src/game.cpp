#include "game.h"
#include "turn.h"
#include "gusano.h"
#include "viga.h"
#include <iostream>
#include <utility>

//Game::Game(Socket& socket_e, ProtectedQueue& queue_e) : proxy(socket_e), queue(queue_e), world(b2Vec2(0.0f, -10.0f)){
Game::Game(Socket& socket_e, ProtectedQueue& queue_e) : queue(queue_e), world(b2Vec2(0.0f, -10.0f)){
	this->world.SetContactListener(&(this->contact_listener));
	
	//lectura de archivo yalm y creacion de vigas y gusanos
	Viga viga(this->world, 0.0f, 0.0f, 0.0f);
	this->water = new Water(this->world, -5, -2, 10, -2);
			
	Gusano* gusano0 = new Gusano(this->world, this->proxy, 0, this->to_remove_gusanos, 0.5f, 0.52f, 0.0f);
	this->gusanos.insert(std::pair<unsigned int, Gusano*>(0,gusano0));
	
	//lectura de archivo yalm y modificacion de constantes de juego
	//this->info.algo = leido
	
		
	//primer paso: mandar al client las posiciones iniciales de las vigas y gusanos
	//std::vector<Viga&>::iterator vigas_it = this->vigas.begin();
	//for (; vigas_it != this->vigas.end(); ++vigas_it) {
		//proxy.send_viga(*it);
	//}
	//std::vector<Gusano&>::iterator gusanos_it = this->gusanos.begin();
	//for (; gusanos_it != this->gusanos.end(); ++gusanos_it) {
		//proxy.send_gusano(*it);
	//}
}

Game::~Game(){
	delete this->water;
}

void Game::play(){
	Turn turn(this->world, this->queue, this->gusanos, this->to_remove_gusanos, this->info);
	std::map<unsigned int, Gusano*>::iterator it = this->gusanos.begin();
	while (it != this->gusanos.end()){
		unsigned int gusano_number = it->first;
		std::cout << "new turn: " << gusano_number << "\n";
		turn.play(gusano_number);
		std::cout << "finish turn\n";
		if (this->gusanos.size() == 0){
			std::cout << "tamanio 0\n";
			break;
		}
		++it;
		if (it  == this->gusanos.end()){
			std::cout << "volver a empezar\n";
			it = this->gusanos.begin();
		}
	}
	std::cout << "salio\n";
	//fin de juego
}
	
	
