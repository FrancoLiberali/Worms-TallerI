#include "thread.h"
#include "proxy.h"
#include "queue.h"
#include <mutex>

#ifndef __RECEIVER_H__
#define __RECEIVER_H__

class Receiver : public Thread{
	private:
		Proxy* proxy;
		std::mutex keep_mutex;
		bool keep_receiving = true;
	public:
		// Crea un objeto receiver. La creacion de este objeto es bloqueante
		// hasta que un jugador se conecte al socket recibido.
		// Una vez conectado, se crea el proxy de comunciacion con el mismo.
		Receiver(Socket& socket, Queue* queue);
		
		~Receiver();
		
		// Devuelve el proxy de comunicacion con el jugador que se conecto
		// al crear el objeto.
		Proxy* getProxy();
		
		// Bucle de recepcion de eventos por parte del proxy, los cuales 
		// se van encolando en la cola protegida recibida al crearse el objeto.
		virtual void run();
		
		// Se finaliza la recepcion de mensajes
		virtual void stop();
		
};

#endif
