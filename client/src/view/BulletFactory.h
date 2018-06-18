#ifndef _BULLET_FACTORY_H
#define _BULLET_FACTORY_H

#include "WormState.h"
#include "BulletView.h"

class BulletFactory{
public:
	static BulletView* createBulletView(WeaponId idWeapon, int id, int dir, int posx,
                         int posy, int angle, SdlScreen& screen, Camera& camera);
};

#endif