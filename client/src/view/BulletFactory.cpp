#include "BulletFactory.h"
#include "SpriteConfigurator.h"
#include "GameException.h"
#include "../sound/SoundManager.h"
#include <iostream>

BulletView* BulletFactory::createBulletView(WeaponId idWeapon, int id, int dir, int posx, int posy,
     int angle, SdlScreen& screen, Camera& camera){
    BulletView* bullet = new BulletView(id, dir,posx, posy, angle, screen, camera);
    try {    
        switch (idWeapon){
            case BAZOOKA:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_bazooka"));
                break;
            case MORTERO:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_mortar"));
                break;
            case G_GRENADE:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_ggrenade"));
                break;
            case R_GRENADE:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_rgrenade"));
                break;
            case BANANA:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_banana"));
                break;
            case HOLY:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_holy"));
                break;
            case DYNAMITE:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_dynamite"));
                break;
            case AIRATTACK:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_airattack"));
                break;
            case FRAGMENT:
                bullet->setSpriteBullet(SpriteConfigurator::Instance().get("bullet_fragment"));
                break;
        }
        bullet->setExplotionSound(EXPLOTION);
        bullet->setSpriteExplosion(SpriteConfigurator::Instance().get("explotion"));
    }catch(GameException& e){
        std::cout<<e.what()<<std::endl;
    }
    return bullet;
}