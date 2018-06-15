#include "game.h"
#include "turn.h"
#include "gusano.h"
#include "viga.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>
//#include "util/yamlparser.h"

Game::Game(MultipleProxy& proxy_e, ProtectedQueue& queue_e, unsigned int map_id, int cant_players_e) 
		: proxy(proxy_e), queue(queue_e), world(b2Vec2(0.0f, -10.0f)), cant_players(cant_players_e){
	this->world.SetContactListener(&(this->contact_listener));
	
	//lectura de archivo yalm "map_id" y creacion de vigas y gusanos
	Viga viga(this->world, 3.0f, 8.0f, 0.0f, this->proxy);
	Viga viga2(this->world, 9.0f, 8.0f, 0.0f, this->proxy);
	Viga viga3(this->world, 3.0f, 18.0f, 0.0f, this->proxy);
	Viga viga4(this->world, 9.0f, 18.0f, 0.0f, this->proxy);

	this->water = new Water(this->world, -10, -10, 20, -10);
	
	std::vector<Gusano*> gusanos;
	Gusano* gusano0 = new Gusano(this->world, this->proxy, this->to_remove_gusanos, 6.5f, 10.48f, 0.0f);
	gusanos.push_back(gusano0);
	Gusano* gusano1 = new Gusano(this->world, this->proxy, this->to_remove_gusanos, 4.0f, 10.48f, 0.0f);
	gusanos.push_back(gusano1);
	//Gusano* gusano2 = new Gusano(this->world, this->proxy, this->to_remove_gusanos, 5.0f, 0.52f, 0.0f);
	//gusanos.push_back(gusano2);
	
	srand(time(0));
	std::random_shuffle(gusanos.begin(), gusanos.end());
	
	//lectura de archivo yalm y modificacion de constantes de juego
	//this->info.algo = leido
	
	// el siguiente gusano para todos los jugadores es el numero 1
	std::cout << cant_players << "\n";
	for (int i = 0; i <= cant_players; i++){
		this->next.push_back(1);
	}
	
	// En el server, cada player tiene sus gusanos 1,2,3, etc para guardarlos
	// en el doble mapa players. El gusano_id es el id unico para cada gusano,
	// con el que el client identificara a ese gusano.
	std::vector<Gusano*>::iterator it = gusanos.begin();
	int player, gusano_number, gusano_id;
	for (player = 1, gusano_number = 1, gusano_id = 1; it != gusanos.end(); player++, gusano_id++, ++it){
		std::cout << player << "\n";
		std::cout << gusano_number << "\n";
		(*it)->setId(player, gusano_number, gusano_id);
		this->players[player][gusano_number] = (*it);
		if (player == cant_players){
			player = 0;
			gusano_number++;
		}
	}
	//aumento de vida a gusanos de jugadores que no completaron
	this->gusanos_per_player = gusano_number;
	if (player != 1){
		for (; player <= cant_players; player++){
			std::map<int, Gusano*>::iterator it2 = this->players[player].begin();  
			for (; it2 != this->players[player].end(); ++it2){
				it2->second->addLife(25);
			}
		}
	}
}

Game::~Game(){
	delete this->water;
	//destruccion de gusanos que quedaron vivos
	std::map<int, std::map<int, Gusano*>>::iterator players_it = this->players.begin();
	for (; players_it != this->players.end(); ++players_it) {
		std::map<int, Gusano*>::iterator gusanos_it = players_it->second.begin();
		for (; gusanos_it != players_it->second.end(); ++gusanos_it) {
			Gusano* gusano = gusanos_it->second;
			delete gusano;
		}
	}
	this->queue.empty();
}

void Game::play(){
	this->queue.empty();
	Turn turn(this->world, this->queue, this->players, this->to_remove_gusanos, this->info, this->proxy);
	
	for (int i = 1; i <= this->cant_players; i++){
		if (this->players.size() == 1){
			break;
		}
		try{
			std::map<int, Gusano*> gusanos = this->players.at(i);
			std::cout << "new turn: " << i << "\n";
			while (true){
				// es while true ya que si el jugador aun existe, se va a poder encontrar un gusano
				try{
					gusanos.at(this->next[i]);
					turn.play(i, this->next[i]);
					this->next[i]++;
					break;
				} catch (std::out_of_range& e){
					// ese gusano ya no existe
					this->next[i]++;
					if (this->next[i] > this->gusanos_per_player){
						// reinicio de gusano a utilizar
						this->next[i] = 1;
					}
				}
			}
		} catch (std::out_of_range& e){
			// ese jugador ya no existe
			continue;
		}
		if (i == this->cant_players){
			// reinicio de ronda
			i = 0;
		}
	}
	std::cout << "salio\n";
	this->proxy.sendGameWon(this->players.begin()->first);
	//fin de juego
}
	
	
