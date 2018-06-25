#include "util/thread.h"
#include "server/proxy.h"
#include "util/queue.h"
#include <mutex>

#ifndef __RECEIVER_H__
#define __RECEIVER_H__

class Receiver : public Thread{
	private:
		Proxy proxy;
		std::mutex keep_mutex;
		bool keep_receiving = true;
	public:
		// Crea un objeto receiver. El mismo es un hilo encargado de recibir
		// todos los mensajes del socket active y encolarlos en la queue.
		// Para recibir los mensajes, se crea el proxy de comunciacion con el client.
		Receiver(Socket active, Queue* queue);
		
		~Receiver();
		
		// Devuelve el proxy de comunicacion con el jugador que se conecto
		// al crear el objeto.
		Proxy& getProxy();
		
		// Bucle de recepcion de eventos por parte del proxy, los cuales 
		// se van encolando en la cola protegida recibida al crearse el objeto.
		virtual void run();
		
		// Se finaliza la recepcion de mensajes
		virtual void stop();
		
		Receiver(Receiver&& other);
		
};

#endif
