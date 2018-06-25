#include "util/thread.h"
#include "server/socket.h"
#include "server/proxy.h"
#include "server/multiple_proxy.h"
#include "util/blocking_queue.h"
#include "server/hall.h"
#include "server/player_info.h"
#include <mutex>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

#ifndef __SERVER_H__
#define __SERVER_H__

class Server : public Thread {
	private:
		std::mutex& syslog_mutex;
		const std::vector<std::string>& maps;
		Socket socket;
		std::map<int, PlayerInfo> players;
		std::mutex mutex;
		MultipleProxy not_playing;
		BlockingQueue hall_queue;
		Hall hall;
		std::mutex keep_mutex;
		bool keep_accepting;
		int cant_players = 0;
	public:
		// Crea un server que se bindea al puerto port.
		// Lanza SocketError en caso de error en el bindeo.
		Server(const char* port, std::mutex& syslog_mutex, const std::vector<std::string>& maps);
		
		~Server() noexcept;
		
		// Ejecuta el ciclo basico del server:
		// Aceptar un cliente.
		// Agregarlo a lista de clientes que no estan jugando.
		// Mandarle todas las salas disponibles.
		// Lanzar un hilo que reciba todos los mensajes del cliente.
		virtual void run();
		
		// Detiene el funcionamiento del servidor.
		virtual void stop();
		
		Server(const Server& other) = delete;
		Server& operator= (const Server& other) = delete;
};
#endif
