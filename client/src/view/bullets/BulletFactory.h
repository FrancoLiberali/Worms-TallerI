#ifndef _BULLET_FACTORY_H
#define _BULLET_FACTORY_H

#include "../WormStateAndWeapon.h"
#include "BulletView.h"

/**
* @class BulletFactory
* Usa el patrón factory para crear la vista de un missil.
* El id del arma debe ser válido.
*/

class BulletFactory{
public:
	static BulletView* createBulletView(WeaponId idWeapon, int id, int dir, int posx,
                         int posy, int angle, SdlScreen& screen, Camera& camera);
};

#endif