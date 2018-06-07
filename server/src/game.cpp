#include "game.h"
#include "turn.h"
#include "gusano.h"
#include "viga.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>

Game::Game(MultipleProxy& proxy_e, ProtectedQueue& queue_e, unsigned int map_id, int cant_players_e) 
		: proxy(proxy_e), queue(queue_e), world(b2Vec2(0.0f, -10.0f)), cant_players(cant_players_e){
	this->world.SetContactListener(&(this->contact_listener));
	
	//lectura de archivo yalm "map_id" y creacion de vigas y gusanos
	Viga viga(this->world, 0.0f, 0.0f, 0.0f, this->proxy);
	
	this->water = new Water(this->world, -5, -2, 10, -2);
	
	std::vector<Gusano*> gusanos;
	
	Gusano* gusano0 = new Gusano(this->world, this->proxy, this->to_remove_gusanos, 0.5f, 0.52f, 0.0f);
	gusanos.push_back(gusano0);
	
	std::random_shuffle(gusanos.begin(), gusanos.end());
	
	//lectura de archivo yalm y modificacion de constantes de juego
	//this->info.algo = leido
	
	std::vector<Gusano*>::iterator it = gusanos.begin();
	int player, gusano_id;
	for (player = 1, gusano_id = 1; it != gusanos.end(); player++, ++it){
		(*it)->setId(player, gusano_id);
		this->players[player][gusano_id] = (*it);
		this->next[player] = 1;
		if (player == cant_players){
			player = 0;
			gusano_id++;
		}
	}
	this->gusanos_per_player = gusano_id;
	for (; player <= cant_players; player++){
		std::map<int, Gusano*>::iterator it2 = this->players[player].begin();  
		for (; it2 != this->players[player].end(); ++it2){
			it2->second->addLife(25);
		}
	}
	
	/*int gusanos_per_player = cant_gusanos / cant_players;
	int rest_gusanos = cant_gusanos - gusanos_per_player * cant_players;
	int player = 1;
	int gusano = 1;
	for (; player <= rest_gusanos; player++, gusano++){
		this->players[player].first = 0;
		for (int i = 0; i <= gusanos_per_player + 1; i++, gusano++){
			this->players[player].second.push_back(gusano);
		}
	}
	for (; player <= cant_players; player++, gusano++){
		this->players[player].first = 0;
		for (int i = 0; i <= gusanos_per_player; i++, gusano++){
			this->players[player].second.push_back(gusano);
			this->gusanos.at(gusano)->addLife(25);
		}
	}*/
	
	
	/*std::map<unsigned int, Gusano*>::iterator gusanos_it = this->gusanos.begin();
	int player;
	for (player = 1; gusanos_it != this->gusanos.end(); ++gusanos_it, player++) {
		unsigned int id = gusanos_it->first;
		this->players[player].push_back(id);
		if (player == cant_players){
			player = 0;
		}
	}
	if (player != 0){
		for (player + 1; player <= cant_players; player++){
			std::vector<unsigned int>::iterator it = this->players.at(player).begin();
			for (; it != this->players.at(player).end(); ++it		*/
			
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
	Turn turn(this->world, this->queue, this->players, this->to_remove_gusanos, this->info, this->proxy);
	
	while (this->players.size() != 1){
		for (int i = 1; i <= this->cant_players; i++){
			try{
				std::map<int, Gusano*> gusanos = this->players.at(i);
				std::cout << "new turn: " << i << "\n";
				while (true){
					try{
						gusanos.at(this->next[i]);
						turn.play(i, this->next[i]);
						this->next[i]++;
					} catch (std::out_of_range& e){
						this->next[i]++;
						if (this->next[i] == this->gusanos_per_player){
							this->next[i] = 1;
						}
					}
				}
			} catch (std::out_of_range& e){
				continue;
			}
		}
	}
	std::cout << "salio\n";
	//fin de juego
			
	
	
	/*std::map<int, std::pair<unsigned int, std::vector<unsigned int>>>::iterator it = this->players.begin();
	while (it != this->players.end()){
		if (this->players.size() == 1){
			std::cout << "tamanio 1\n";
			break;
		}
		int player_id = it->first;
		std::cout << "new turn: " << player_id << "\n";
		unsigned int actual_pos = it->second.first;
		std::vector<unsigned int> gusanos_ids = it->second.second;
		unsigned int actual_id = gusanos_ids[actual_pos];
		turn.play(player_id, actual_id);
		it->second.first++;
		if (it->second.first >= gusanos_ids.size()){
			it->second.first = 0;
		}
		++it;
		if (it == this->players.end()){
			std::cout << "volver a empezar\n";
			it = this->players.begin();
		}
	}
	std::cout << "salio\n";
	//fin de juego*/
}
	
	
