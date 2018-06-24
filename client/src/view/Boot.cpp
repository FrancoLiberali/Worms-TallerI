#include "Boot.h"

#include "TextureManager.h"
#include "TextManager.h"
#include "FontManager.h"
#include "SpriteConfigurator.h"
#include "../sound/SoundManager.h"
#include "../../config.h"
#include <iostream>

#define W_WIDHT 800
#define W_HEIGHT 600

void Boot::init(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	screen.init("WORMS ", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, W_WIDHT, W_HEIGHT, 
        SDL_WINDOW_HIDDEN);	
	TextManager::Instance().init(screen.getRenderer());
    TextureManager::Instance().init(W_WIDHT, W_HEIGHT);
	FontManager::Instance().init(screen.getRenderer());
	SoundManager::Instance().init();
    loadSprites();
	loadMenuWeapon();
	loadSounds();
	loadFonts();
}

void Boot::loadSprites(){
	try {
		// worm
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wwalk.png", "caminar", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wdie.png", "morir", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wflyup.png", "saltar", screen.getRenderer());
		
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/grave2.png", "cripta", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wstatic.png", "static", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wbaz.png", "bazooka", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wbaz.png", "mortero", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wdynbak.png", "dinamita", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wthrgrn.png", "ggranada", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wthrcls.png", "rgranada", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wthrhgr.png", "holy", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wairtlk.png", "radio", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wbsbaim.png", "bate", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wtelbak.png", "teleport", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/wthrban.png", "banana", screen.getRenderer());


		SpriteConfigurator::Instance().add("caminar", 60, 60, 15, true);
		SpriteConfigurator::Instance().add("saltar", 60, 60, 2, true);
		SpriteConfigurator::Instance().add("morir", 60, 60, 60, false);
		SpriteConfigurator::Instance().add("cripta", 60, 60, 20, false);
		SpriteConfigurator::Instance().add("static", 60 ,60, 98, true);

		SpriteConfigurator::Instance().add("bazooka", 60, 60, 32, false, 16);
		SpriteConfigurator::Instance().add("mortero", 60, 60, 32, false, 16);
		SpriteConfigurator::Instance().add("dinamita", 60, 60, 10, true);
		SpriteConfigurator::Instance().add("ggranada", 60, 60, 32, false, 16);
		SpriteConfigurator::Instance().add("rgranada", 60, 60, 32, false, 16);
		SpriteConfigurator::Instance().add("holy", 60, 60, 32, false, 16);
		SpriteConfigurator::Instance().add("radio", 60, 60, 10, true);
		SpriteConfigurator::Instance().add("bate", 60, 60, 32, false, 16);
		SpriteConfigurator::Instance().add("teleport", 60, 60, 10, false);
		SpriteConfigurator::Instance().add("banana", 60, 60, 32, false, 16);

		// projectiles

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/bazzoka.png", "bullet_bazooka", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/mortar.png", "bullet_mortar", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/airmisl.png", "bullet_airmisl", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/dynamite.png", "bullet_dynamite", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/hgrenade.png", "bullet_holy", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/ggrenade.png", "bullet_ggrenade", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/rgrenade.png", "bullet_rgrenade", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/banana.png", "bullet_banana", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/misiles/fragment.png", "bullet_fragment", this->getScreen().getRenderer());

		SpriteConfigurator::Instance().add("bullet_airmisl", 60, 60, 32, true, 23);
		SpriteConfigurator::Instance().add("bullet_dynamite", 60, 60, 129, true);
		SpriteConfigurator::Instance().add("bullet_holy", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_ggrenade", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_rgrenade", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_bazooka", 60, 60, 32, true, 23);
		SpriteConfigurator::Instance().add("bullet_mortar", 60, 60, 32, true, 23);
		SpriteConfigurator::Instance().add("bullet_banana", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_fragment", 60, 60, 6, true);
		//Vigas
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/vigah.png", "viga", screen.getRenderer());

		//imagenes
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/win.png", "win", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/lose.png", "lose", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/messageBox.png", "message", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/reloj.png", "reloj", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/sky3.png", "sky3.png", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/marea1.png", "marea1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/marea2.png", "marea2", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/marea3.png", "marea3", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/marea4.png", "marea4", screen.getRenderer());

		// explosiones
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/circle25.png", "circle25", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/explotion.png", "explotion", screen.getRenderer());

		SpriteConfigurator::Instance().add("circle25", 50, 50, 8, false);
		SpriteConfigurator::Instance().add("explotion", 134, 134, 12, false);

		} catch (GameException & e) {
            std::cerr << e.what() << std::endl;
		}
}

void Boot::loadMenuWeapon(){
	try {

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/MenuWeapon.png", "MenuWeapon", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/aim.png", "aim", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/ok.png", "ok", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/bazooka.1.png", "bazooka.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/bazooka.2.png", "bazooka.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/mortar.1.png", "mortar.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/mortar.2.png", "mortar.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/grenade.1.png", "g_grenade.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/grenade.2.png", "g_grenade.2", screen.getRenderer());
		
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/cluster.1.png", "r_grenade.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/cluster.2.png", "r_grenade.2", screen.getRenderer());
		
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/banana.1.png", "banana.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/banana.2.png", "banana.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/hgrenade.1.png", "hgrenade.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/hgrenade.2.png", "hgrenade.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/dynamite.1.png", "dynamite.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/dynamite.2.png", "dynamite.2", screen.getRenderer());
	
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/baseball.1.png", "baseball.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/baseball.2.png", "baseball.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/airstrke.1.png", "airstrke.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/airstrke.2.png", "airstrke.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/teleport.1.png", "teleport.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ "/resource/images/menuWeapon/teleport.2.png", "teleport.2", screen.getRenderer());

		/*inicia el manejo del texto*/
		TextManager::Instance().init(screen.getRenderer());
		TextManager::Instance().loadFont(Arial16);
		TextManager::Instance().loadFont(Arial12);

	} catch (GameException & e) {
		std::cout << e.what() << std::endl;	
	}
}

void Boot::loadSounds(){
	SoundManager::Instance().loadMusic(BACKGROUND, _INSTALL_PATH_ "/resource/sounds/background.wav");
	SoundManager::Instance().loadSound(EXPLOTION, _INSTALL_PATH_ "/resource/sounds/explotion2.wav");
	SoundManager::Instance().loadSound(FUSE, _INSTALL_PATH_ "/resource/sounds/FUSE.wav");
	SoundManager::Instance().loadSound(HOLY_S, _INSTALL_PATH_ "/resource/sounds/holy.wav");
	SoundManager::Instance().loadSound(BANANA_S, _INSTALL_PATH_ "/resource/sounds/BananaImpact.wav");
	SoundManager::Instance().loadSound(JUMP_S, _INSTALL_PATH_ "/resource/sounds/jump.wav");
	SoundManager::Instance().loadSound(SHOOT, _INSTALL_PATH_ "/resource/sounds/handgunfire.wav");
	SoundManager::Instance().loadSound(COMMUNICATOR, _INSTALL_PATH_ "/resource/sounds/communicator.wav");
	SoundManager::Instance().loadSound(TELELEPORT_S, _INSTALL_PATH_ "/resource/sounds/teleport.wav");
	SoundManager::Instance().loadSound(BAT_IMPACT, _INSTALL_PATH_ "/resource/sounds/bat_impact.wav");
	SoundManager::Instance().loadSound(BAT_JINGLE, _INSTALL_PATH_ "/resource/sounds/bat_jingle.wav");
	SoundManager::Instance().loadSound(BYE, _INSTALL_PATH_ "/resource/sounds/byebye.wav");
	SoundManager::Instance().loadSound(AIRSTRIKE, _INSTALL_PATH_ "/resource/sounds/airstrike.wav" );
}

void Boot::loadFonts(){
	try{
		FontManager::Instance().openFont("arialbd", _INSTALL_PATH_ "/resource/font/arialbd.ttf", 14);
		FontManager::Instance().openFont("reloj", _INSTALL_PATH_ "/resource/font/reloj.ttf", 25);
	} catch (SdlException& e){
		std::cout << e.what() << std::endl;	
	}
}

SdlScreen& Boot::getScreen(){
    return screen;
}