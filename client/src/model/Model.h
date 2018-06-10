#ifndef _CLIENT_MODEL
#define _CLIENT_MODEL

#include "GameControllerProxy.h"

#include <map>
/*Modelo del cliente*/
class Model {
private:
	int idWormSelected;
	int idJugador;
	std::string namePlayer;
	GameControllerProxy* gcp;
	std::map<int, std::string> players;
public:
	Model();
	~Model();
	void WormMove(const int dir);
	void WormJump(const int dir);
	void WormWeapon(const int idWeapon);
	int getIdWormSelected();
	void setGameControllerProxy(GameControllerProxy* gcp);
	void setIdPlayer(int idJugador);
	void addPlayers(int id, std::string name);
	std::string getPlayerById(int id);
	void selectWorm(int id);
	void setNamePlayer(std::string name);
	std::string getNamePlayer();
};

#endif