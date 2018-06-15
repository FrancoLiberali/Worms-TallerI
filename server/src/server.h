#include "thread.h"
#include "socket.h"
#include "proxy.h"
#include "multiple_proxy.h"
#include "blocking_queue.h"
#include "initiador.h"
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
		Socket socket;
		std::vector<std::pair<std::string, Receiver*>> players;
		MultipleProxy not_playing;
		BlockingQueue hall_queue;
		std::map<std::string, Room*> rooms;
		std::mutex rooms_mutex;
		Initiador* initiador;
		std::mutex keep_mutex;
		bool keep_accepting;
		int cant_players = 0;
	public:
		// Crea un server que se bindea al puerto port.
		// Lanza SocketError en caso de error en el bindeo.
		Server(const char* port, std::mutex& syslog_mutex);
		
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
