#include "game/game.h"
#include "game/turn.h"
#include "game/viga.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include "game/game_finished.h"
#include "util/yamlparser.h"
#include <string>

#define X_GRAVITY 0
#define Y_GRAVITY -10

#define VIGA "viga"
#define GUSANO "gusano"

Game::Game(MultipleProxy& proxy_e, ProtectedQueue& queue_e, const std::string& map_name, std::vector<int> players_ids_e) 
		: proxy(proxy_e), queue(queue_e), world(b2Vec2(X_GRAVITY, Y_GRAVITY)), players_ids(players_ids_e), 
		factory(world, proxy, to_remove_gusanos, info) {
	this->world.SetContactListener(&(this->contact_listener));
	
	std::vector<Gusano> gusanos;
	//lectura de archivo yalm "map_name" y creacion de vigas y gusanos
	YAMLParser parser;
	std::vector<ElementInfo> elements;
	parser.cargarConfig(map_name, elements, this->info);
	this->info.setAmmunition(); 
	
	this->factory.createDelimiters(this->delimiters);
	this->proxy.sendMapBackground(this->info.map_background);	
	
	std::vector<ElementInfo>::iterator info_it = elements.begin();
	for (; info_it != elements.end(); ++info_it){
		if (info_it->tipo.compare(VIGA) == 0){
			this->factory.createViga(*info_it);
		}
		else if (info_it->tipo.compare(GUSANO) == 0){
			this->factory.createGusano(gusanos, *info_it);
		}
	}
	
	srand(time(0));
	//para que los gusanos toquen en orden aleatorio
	std::random_shuffle(gusanos.begin(), gusanos.end());
	//para que los turnos sean en un orden aletorio
	std::random_shuffle(players_ids.begin(), players_ids.end());
	
	// el siguiente gusano para todos los jugadores es el numero 1
	for (int i = 0; i < this->players_ids.size(); i++){
		this->next.push_back(1);
	}
	
	// En el server, cada player tiene sus gusanos 1,2,3, etc para guardarlos
	// en el doble mapa players. El gusano_id es el id unico para cada gusano,
	// con el que el client identificara a ese gusano.
	std::vector<Gusano>::iterator it = gusanos.begin();
	int player, gusano_number, gusano_id;
	for (player = 0, gusano_number = 1, gusano_id = 1; it != gusanos.end(); player++, gusano_id++, ++it){
		it->setId(this->players_ids[player], gusano_number, gusano_id);
		this->players[this->players_ids[player]].insert(std::pair<int, Gusano>(gusano_number, std::move(*it)));
		if (player == this->players_ids.size() - 1){
			player = -1;
			gusano_number++;
		}
	}
	//aumento de vida a gusanos de jugadores que no completaron
	this->gusanos_per_player = gusano_number;
	if (player != 0){
		for (; player < this->players_ids.size(); player++){
			std::map<int, Gusano>::iterator it2 = this->players[this->players_ids[player]].begin();  
			for (; it2 != this->players[this->players_ids[player]].end(); ++it2){
				it2->second.addLife(this->info.worm_extra_life);
			}
		}
	}
	this->play();
}

Game::~Game(){
	this->queue.empty();
}

void Game::play(){
	this->queue.empty();
	Turn turn(this->world, this->queue, this->players, this->to_remove_gusanos, 
		this->info, this->proxy, this->factory);
	
	try {
		for (int i = 0; i < this->players_ids.size(); i++){
			int player_id = this->players_ids[i];
			if (this->players.size() == 1){
				break;
			}
			try{
				std::map<int, Gusano>& gusanos = this->players.at(player_id);
				while (true){
					// es while true ya que si el jugador aun existe, se va a poder encontrar un gusano
					try{
						gusanos.at(this->next[i]);
						turn.play(player_id, this->next[i]);
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
			if (i == this->players_ids.size() - 1){
				// reinicio de ronda
				i = -1;
			}
		}
	} catch (GameFinished& e){
	}
	this->proxy.sendGameWon(this->players.begin()->first);
}
	
	
