#include "game.h"
#include "socket.h"
#include "protected_queue.h"
#include "proxy.h"
#include "multiple_proxy.h"
#include "fake_proxy/mok_proxy.h"
#include <iostream>
#include "receiver.h"
#include <vector>
#include <arpa/inet.h>
#include <string>

int main(int argc, char** argv) {
	if (argc < 2){
		return 1;
	}
	Socket socket;
	socket.bind(argv[1]);
	ProtectedQueue queue;
	int cant_players = 1;
	std::vector<Thread*> receivers;
	//conexion del primer jugador
	Receiver* receiver = new Receiver(socket, queue);
	Proxy* proxy = receiver->getProxy();
	
	receiver->start();
	receivers.push_back(receiver);
	proxy->sendPlayerId(cant_players);
	MultipleProxy to_send;
	to_send.add(proxy);
	
	//se espera que el primer jugador qu se conecto envie el numero de jugadores de la partida y el mapa que quiere jugar
	unsigned int map_id = 0;
	int max_players = 0;
	bool waiting_message = true;
	while(waiting_message){
		if (!queue.isEmpty()){
			std::cout << "hay evento\n";
			//no es posible generar raise condition porque del otro lado solo meten asi que si 
			//no estaba vacia tampoco lo estara ahora
			char* msj = queue.front();
			queue.pop();
			if (msj[0] == 1){
				map_id = ntohl(*(reinterpret_cast<unsigned int*>(msj + 1)));
				max_players = ntohl(*(reinterpret_cast<int*>(msj + 5)));
				waiting_message = false;
			}
			delete[] msj;
		}
	}
	
	//luego se espera la coneccion de la cantidad de jugadores que el primer jugador indico
	// (aun no se encuentra implementada una solucion para desconecciones de jugadores durante esta etapa)
	while (cant_players < max_players){
		cant_players++;
		Receiver* new_receiver = new Receiver(socket, queue);
		Proxy* new_proxy = new_receiver->getProxy();
		to_send.add(new_proxy);
		new_proxy->sendPlayerId(cant_players);
		receivers.push_back(new_receiver);
		new_receiver->start();
	}
	// uan vez todo conectados, se mira que la cola de mensajes los nombres de los mismos, 
	// no necesariamente en el orden que se coenctaron
	std::map<int, std::string> names;
	while (names.size() != cant_players){
		while (!queue.isEmpty()){
			std::cout << "hay evento\n";
			char* msj = queue.front();
			queue.pop();
			if (msj[0] == 0){
				int player_id = ntohl(*(reinterpret_cast<unsigned int*>(msj + 1)));
				int name_len = ntohl(*(reinterpret_cast<unsigned int*>(msj + 5)));
				std::string name(msj + 9, name_len);
				names[player_id] = name;
				std::cout << name << "\n";
			}
			delete[] msj;
		}
	}
	// se envia a todos los jugadores los nombres de los demas
	std::map<int, std::string>::iterator it = names.begin();
	for (; it != names.end(); ++it){
		to_send.sendPlayerName(it->first, it->second);
	}
	Game game(to_send, queue, map_id, cant_players);
	game.play();
	//fin de juego, se dejan de recibir mensajes
	std::vector<Thread*>::iterator it2 = receivers.begin();
	for (; it2 != receivers.end(); ++it2){
		(*it2)->stop();
		(*it2)->join();
		delete (*it2);
	}
	return 0;
}
