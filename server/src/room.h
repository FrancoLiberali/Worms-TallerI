#include "thread.h"
#include "multiple_proxy.h"
#include "proxy.h"
#include <vector>
#include <string>

#ifndef __ROOM_H__
#define __ROOM_H__

class Room : public Thread{
	private:
		const std::string name;
		const std::string map_name;
		const int max_players;
		std::map<int, const std::string&> names;
		MultipleProxy proxy;
		ProtectedQueue queue;
		bool active = false;
		
	public:
		//Crea un objeto Room, el cual es la sala en la que los jugadores
		// esperan que los demas se conecten y luego se juega la partida.
		Room(const std::string name, const std::string map_name_e, const int max_players_e);
		
		Room(Room&& other);
		
		~Room();
		
		// Devuelve el nombre de la sala
		const std::string& getName();
		
		// Agrega un jugador a la sala.
		// Avisa a todos los demas jugadores de su coneccion
		// y envia al recien conectado la informacion de todos los que
		// ya se encontraban en la sala
		void add(const int player_id, const std::string& player_name, Proxy& player_proxy);
		
		// Saca a un jugador de la sala y avisa a los demas jugadores de su salida.
		void erase(int player_id);
		
		// Corre la partida.
		virtual void run();
		
		// No hace nada, la partida no se puede parar hasta que no termine.
		virtual void stop();
		
		// Devuelve true si la partida comenzo o false
		// si se sigue esperando que se conectan mas jugadores
		bool isActive();
		
		// Devuelve la cantidad de jugadores conectados a
		// la sala actualmente
		int cantPlayers();
		
		//Devuelve la cantidad maxima de jugadores de la sala,
		// la cantidad que es necesaria para que la partida comienze.
		int maxPlayers();
		
		// Devuelve el nombre del mapa con el que se creo la sala
		// y que se va a jugar cuando comience la partida
		const std::string& mapName();
};

#endif
	
