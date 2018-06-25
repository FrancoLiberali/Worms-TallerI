#ifndef _CLIENT_EVENT_RECEIVER_H
#define _CLIENT_EVENT_RECEIVER_H 

#include "../common/Queue.h"
#include "../common/Thread.h"
#include "../exception/socket_error.h"
#include "../ProxyClient.h"
#include "../model/Model.h"
#include "../PreGameManager.h"
#include "event/Event.h"

class Model;
class ProxyClient;
class PreGameManager;


/**
* @class ClientEventReceiver
* Recive todos los eventos del server los encola en una cola bloqueante
* que después son desencolados y encolados a la cola princiopal de eventos del 
* EventHandler. Corre en un hilo propio.
*/
class ClientEventReceiver : public Thread{
private:
	Queue<Event*>& q;
	ProxyClient& proxy;
	Model& model;
	mainView& view;
	PreGameManager& preGame;
	bool closed;
	bool isPreGameEvent(int t);
	void process(int t);
public:
	ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& eventQueue, 
	Model& model, mainView& view, PreGameManager& preGame);
	~ClientEventReceiver();
	virtual void run() override;
	void stop();
	bool isClosed() const;
	void keepPlaying();
	void clean();
};

#endif
