#include "game.h"
#include "turn.h"
#include "gusano.h"
#include "viga.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include "game_finished.h"
#include "util/yamlparser.h"
#include <string>

#define MAP_OFFSET 25
#define WATER_DEPPNESS 3

Game::Game(MultipleProxy& proxy_e, ProtectedQueue& queue_e, std::string& map_name, std::vector<int> players_ids_e) 
		: proxy(proxy_e), queue(queue_e), world(b2Vec2(0.0f, -10.0f)), players_ids(players_ids_e){
	this->world.SetContactListener(&(this->contact_listener));
	
	std::vector<Gusano> gusanos;
	//lectura de archivo yalm "map_name" y creacion de vigas y gusanos
	YAMLParser parser;
	std::vector<ElementInfo> elements;
	parser.cargarConfig(map_name, elements, this->info);
	this->info.setAmmunition(); 
	
	//se agregan al mapa espacios vacios a izquierda, derecha y arriba, y abajo un pequenio espacio para el agua
	float down_limit = info.map_height + WATER_DEPPNESS + MAP_OFFSET;
	float right_limit = info.map_widht + 2 * MAP_OFFSET;
	this->proxy.sendMapDimentions(right_limit, down_limit);
	this->proxy.sendMapBackground(this->info.map_background);
	
	//se agregan delimitadores de mapa
	this->delimiters.push_back(std::move(Delimiter(this->world, 0, 0, 0, -down_limit))); //left
	this->delimiters.push_back(std::move(Delimiter(this->world, 0, 0, right_limit, 0)));//up
	this->delimiters.push_back(std::move(Delimiter(this->world, right_limit, 
									0, right_limit, -down_limit)));//right
	this->delimiters.push_back(std::move(Delimiter(this->world, 0, -down_limit, 
							right_limit, -down_limit)));//down			
	//this->water = new Water(this->world, 0, -down_limit + WATER_DEPPNESS, right_limit, -down_limit + WATER_DEPPNESS);
	
	std::vector<ElementInfo>::iterator info_it = elements.begin();
	for (; info_it != elements.end(); ++info_it){
		std::cout << "hay elem\n";
		if (info_it->tipo.compare("viga") == 0){
			std::cout << "crear viga\n";
			Viga viga(this->world, info_it->x + MAP_OFFSET, -info_it->y - MAP_OFFSET, info_it->angulo, this->proxy);
		}
		else if (info_it->tipo.compare("gusano") == 0){
			std::cout << "crear gusano\n";
			Gusano gusano(this->world, this->proxy, this->to_remove_gusanos,
				info_it->x + MAP_OFFSET, -info_it->y - MAP_OFFSET, info_it->angulo);
			gusanos.push_back(std::move(gusano));
		}
	}
	
	srand(time(0));
	//para que los gusanos toquen en orden aleatorio
	std::random_shuffle(gusanos.begin(), gusanos.end());
	//para que los turnos sean en un orden aletorio
	std::random_shuffle(players_ids.begin(), players_ids.end());
	
	// el siguiente gusano para todos los jugadores es el numero 1
	std::cout << this->players_ids.size() << "\n";
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
				it2->second.addLife(25);
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
	Turn turn(this->world, this->queue, this->players, this->to_remove_gusanos, this->info, this->proxy);
	
	try {
		for (int i = 0; i < this->players_ids.size(); i++){
			int player_id = this->players_ids[i];
			if (this->players.size() == 1){
				break;
			}
			try{
				std::map<int, Gusano>& gusanos = this->players.at(player_id);
				std::cout << "new turn: " << player_id << "\n";
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
	std::cout << "salio\n";
	this->proxy.sendGameWon(this->players.begin()->first);
	//fin de juego
}
	
	
