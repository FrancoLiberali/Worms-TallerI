#include "BulletFactory.h"
#include "../../exception/GameException.h"
#include "BazookaView.h"
#include "MortarView.h"
#include "GreenGrenadeView.h"
#include "RedGrenadeView.h"
#include "BananaView.h"
#include "HolyView.h"
#include "DynamiteView.h"
#include "AirMissileView.h"

#include "FragmentView.h"

#include <iostream>
#include "../../sound/SoundManager.h"

BulletView* BulletFactory::createBulletView(WeaponId idWeapon, int id, int dir, int posx, int posy,
     int angle, SdlScreen& screen, Camera& camera){
    try {    
        switch (idWeapon){
            case BAZOOKA:
                SoundManager::Instance().playSound(SHOOT);
                return new BazookaView(id, dir, posx, posy, angle, screen, camera);
                break;
            case MORTERO:
                SoundManager::Instance().playSound(SHOOT);
                return new MortarView(id, dir, posx, posy, angle, screen, camera);
                break;
            case G_GRENADE:
                return new GreenGrenadeView(id, dir, posx, posy, angle, screen, camera);
                break;
            case R_GRENADE:
                return new RedGrenadeView(id, dir, posx, posy, angle, screen, camera);
                break;
            case BANANA:
                SoundManager::Instance().playSound(BANANA_S);
                return new BananaView(id, dir, posx, posy, angle, screen, camera);
                break;
            case HOLY:
                SoundManager::Instance().playSound(HOLY_S);
                return new HolyView(id, dir, posx, posy, angle, screen, camera);
                break;
            case DYNAMITE:
                return new DynamiteView(id, dir, posx, posy, angle, screen, camera);
                break;
            case AIRATTACK:
                return new AirMissileView(id, dir, posx, posy, angle, screen, camera);
                break;
            case FRAGMENT:
                return new FragmentView(id, dir, posx, posy, angle, screen, camera);
                break;
        }
    }catch(GameException& e){
        std::cout<<e.what()<<std::endl;
    }
    return nullptr; //nunca debería llegar
}