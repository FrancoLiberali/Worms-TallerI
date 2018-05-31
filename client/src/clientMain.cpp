#include <iostream>
#include <string>
#include "controller/ClientEventReceiver.h"
#include "controller/ClientCommandSender.h"
#include "view/View.h"
#include "controller/EventHandler.h"
#include "common/Queue.h"
#include "controller/Event.h"


#define W_WIDHT 800
#define W_HEIGHT 600

int main(int argc, char const *argv[])
{
	//Le pasamos el archivo a leer, deberia ser el socket
	std::string socket = "socket.txt";

	//cola de eventos a recibir
	Queue<Event*> eventQueue;
	ClientEventReceiver eventReceiver(socket, eventQueue);
	eventReceiver.start();
	
	//cola de comandos a enviar
	Queue<ClientCommand*> commandsQueue;
	ClientCommandSender commmandSender(socket, commandsQueue);
	commmandSender.start();

	EventHandler ehandler;

	View clientView(ehandler,W_WIDHT, W_HEIGHT);
	ehandler.setView(&clientView);
	//return 0;
	//Game loop
	int step = 0;
	while(clientView.isOpen()){
		SDL_Event e;
		SDL_WaitEvent(&e);
		//std::cout<<"Se intrudujo un evento" << std::endl;
		switch (e.type){
			case SDL_QUIT:
				std::cout<<"cerrar" << std::endl;			
				clientView.close();
				commmandSender.stop();
				eventReceiver.stop();
				break;
			case SDL_MOUSEMOTION:
				std::cout << e.motion.x << "," << e.motion.y << std::endl;
                break;
		}

		//desencolo los eventos del server
		while (!eventQueue.empty()){
			//std::string msg = eventQueue.pop();
			//std::cout<< msg << std::endl;
			ehandler.add(eventQueue.pop());
		}
		clientView.update();
		step++;
	}
	commmandSender.join();
	eventReceiver.join();

	return 0;
}
