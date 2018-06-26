#include "GameClient.h"
#include "controller/ClientEventReceiver.h"
#include "controller/ClientCommandSender.h"
#include "controller/EventHandler.h"
#include "controller/event/Event.h"
#include "controller/Controller.h"
#include "model/GameControllerProxy.h"
#include "model/Model.h"
#include "manager/Boot.h"
#include "view/mainView.h"
#include "common/Queue.h"
#include "PreGameManager.h"

#include <chrono>
#include <ctime>
#include <thread>

#include <iostream>

GameClient::GameClient(ProxyClient& proxy, std::string nameClient)
    :proxy(proxy), name(nameClient){};

void GameClient::run(){

	//cola de comandos a enviar
	Queue<ClientCommand*> commandsQueue;
	ClientCommandSender commmandSender(proxy, commandsQueue);
	commmandSender.start();

	//manejador de eventos
	EventHandler ehandler;

	//cargamos todas las texturas y el screen principal
	Boot boot;
	boot.init();

	Camera camera(boot.getScreen().getWidth(), boot.getScreen().getHeight());

	mainView clientView(ehandler, boot.getScreen(), camera);
	ehandler.setView(&clientView);

	GameControllerProxy gcp(commandsQueue);

	Model model;
	model.setGameControllerProxy(&gcp);
	model.setNamePlayer(name);
	proxy.addModel(&model);
	ehandler.setModel(&model);

	PreGameManager preGame(proxy);

	//cola de eventos a recibir
	Queue<Event*> eventQueue; 
	ClientEventReceiver eventReceiver(proxy, eventQueue, model, clientView, preGame);
	eventReceiver.start();

	model.setComunnication(&commmandSender, &eventReceiver);

	Controller controller(model, clientView);
	
	if (!preGame.showHall()){
		commandsQueue.push(nullptr);//se cierrar encolar nullpttr
		eventReceiver.stop();
		commmandSender.join();
		eventReceiver.join();
		return;
	}
	printf("Espere a otros jugadores\n");

	//Game loop
	SDL_Event e;
	double extra = 0;
	while(clientView.isOpen() ){
		auto t_start = std::chrono::high_resolution_clock::now();

		while(SDL_PollEvent(&e) != 0)
			controller.handle(e);

		//Chequeo del mouse para saber si se debe mover la camara
		controller.checkMouseState(e, ehandler);
		//Desencolo los eventos del server
		while (!eventQueue.empty()){
			ehandler.add(eventQueue.pop());
		}
		clientView.update();

		auto t_end = std::chrono::high_resolution_clock::now();
		double time_delta = (std::chrono::duration<double, std::micro>(t_end-t_start)).count();
		
		int to_sleep = int(double(1000000/60) - time_delta - extra);
		if (to_sleep >= 0){
			std::this_thread::sleep_for(std::chrono::microseconds(to_sleep));
			extra = 0;
		} else {
			extra = -to_sleep;
		}
	}
	if (controller.isPlaying())
		preGame.showResult();
	commandsQueue.push(nullptr);//se cierra al  encolar nullpttr
	eventReceiver.stop();
	commmandSender.join();
	eventReceiver.join();
}