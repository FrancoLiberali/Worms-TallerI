#include <iostream>
#include <string>
#include "controller/ClientEventReceiver.h"
#include "view/View.h"
#include "controller/EventHandler.h"
#include "common/Queue.h"

#define W_WIDHT 800
#define W_HEIGHT 600

int main(int argc, char const *argv[])
{
	//Le pasamos el archivo a leer, deberia ser el socket
	std::string socket = "socket.txt";

	Queue eventQueue;
	ClientEventReceiver eventReceiver(socket, eventQueue);
	eventReceiver.start();
	EventHandler ehandler;
	View clientView(ehandler,W_WIDHT, W_HEIGHT);

	//Game loop

	while(clientView.isOpen()){
		SDL_Event e;
		SDL_WaitEvent(&e);
		//std::cout<<"Se intrudujo un evento" << std::endl;
		if (e.type == SDL_QUIT){
			std::cout<<"cerrar" << std::endl;			
			clientView.close();
		}

		//desencolo los eventos del server
		while (!eventQueue.empty()){
			std::string msg = eventQueue.pop();
			//std::cout<< msg << std::endl;
			ehandler.add(msg);
		}

		clientView.update();
	}

	eventReceiver.join();
	return 0;
}
