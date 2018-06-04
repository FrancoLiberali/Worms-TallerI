#ifndef _CLIENT_MODEL
#define _CLIENT_MODEL

#include "GameControllerProxy.h"

#include <map>
/*Modelo del cliente*/
class Model {
private:
	int idWormSelected;
	GameControllerProxy& gcp;
public:
	Model(GameControllerProxy& gcp);
	~Model();
	void KeyWormMove(int dir);
	void KeyWormJump();
	void leftClick();
};

#endif