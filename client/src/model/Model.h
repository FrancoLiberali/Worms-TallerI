#ifndef _CLIENT_MODEL
#define _CLIENT_MODEL

#include "GameControllerProxy.h"

#include <map>
/*Modelo del cliente*/
class Model {
private:
	int idWormSelected;
	int idJugador;
	GameControllerProxy& gcp;
public:
	Model(GameControllerProxy& gcp);
	~Model();
	void WormMove(const int dir);
	void WormJump(const int dir);
	void WormWeapon(const int idWeapon);
	int getIdWormSelected();
};

#endif