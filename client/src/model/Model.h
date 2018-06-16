#ifndef _CLIENT_MODEL
#define _CLIENT_MODEL

#include "GameControllerProxy.h"
#include "../controller/ClientEventReceiver.h"
#include "../controller/ClientCommandSender.h"

class ClientCommandSender;
class ClientEventReceiver;

#include <map>
/*Modelo del cliente*/
class Model {
private:
	int idWormSelected;
	int idJugador;
	std::string namePlayer;
	GameControllerProxy* gcp;
	ClientCommandSender * sender;
	ClientEventReceiver * receiver;
	std::map<int, std::string> players;
public:
	Model();
	~Model();
	void WormMove(const int dir);
	void WormJump(const int dir);
	void WormWeapon(const int idWeapon);
	void AimChangeAngle(const int delta);
	void chargePower();
	void WormShoot();
	void countDown(int time);

	int getIdWormSelected();
	void setGameControllerProxy(GameControllerProxy* gcp);
	void setIdPlayer(int idJugador);
	void addPlayers(int id, std::string name);
	std::string getPlayerById(int id);
	void selectWorm(int id);
	void setNamePlayer(std::string name);
	std::string getNamePlayer();
	bool isPlayer(int id);
	void setComunnication(ClientCommandSender* sender, ClientEventReceiver* receiver);
	void closeComunnication();
};

#endif