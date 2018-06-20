#include "GameClient.h"
#include "controller/ClientEventReceiver.h"
#include "controller/ClientCommandSender.h"
#include "controller/EventHandler.h"
#include "controller/Event.h"
#include "controller/Controller.h"
#include "model/GameControllerProxy.h"
#include "model/Model.h"
#include "view/Boot.h"
#include "view/mainView.h"
#include "common/Queue.h"
#include "PreGameManager.h"

#include <iostream>

GameClient::GameClient(ProxyClient& proxy, std::string nameClient)
    :proxy(proxy), name(nameClient){};

void GameClient::run(){

	//cola de comandos a enviar
	Queue<ClientCommand*> commandsQueue;
	ClientCommandSender commmandSender(proxy, commandsQueue);
	commmandSender.start();

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
	//proxy.addModel(&model);

	PreGameManager preGame(proxy);
	//cola de eventos a recibir
	Queue<Event*> eventQueue; 
	ClientEventReceiver eventReceiver(proxy, eventQueue, model, clientView, preGame);
	eventReceiver.start();

	model.setComunnication(&commmandSender, &eventReceiver);

	Controller controller(model, clientView);
	
	//Enviamos el nombre del jugodor
	proxy.sendName(name);
	preGame.showHall();

	printf("INICIO DEL JUEGO \n");
	//Game loop
	SDL_Event e;
	while(clientView.isOpen() ){
		while(SDL_PollEvent(&e) != 0)
			controller.handle(e);
		//Chequeo del mouse para saber si se debe mover la camara
		controller.checkMouseState(e, ehandler);
		//desencolo los eventos del server
		while (!eventQueue.empty()){
			ehandler.add(eventQueue.pop());
		}
		clientView.update();
		//AGREGAR SLEEP
	}
	commandsQueue.push(nullptr);
	eventReceiver.stop();
	commmandSender.join();
	eventReceiver.join();
}