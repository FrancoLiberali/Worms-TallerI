#include "Boot.h"

#include "TextureManager.h"
#include "TextManager.h"
#include "FontManager.h"
#include "SpriteConfigurator.h"
#include "../sound/SoundManager.h"
#include "../../config.h"
#include "path.h"
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
		TextureManager::Instance().load(_INSTALL_PATH_ WWALK_SPRITE, "caminar", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WDIE_SPRITE, "morir", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WJUMP_SPRITE, "saltar", screen.getRenderer());
		
		TextureManager::Instance().load(_INSTALL_PATH_ GRAVE_SPRITE, "cripta", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ STATIC_SPRITE, "static", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WBAZZOKA_SPRITE, "bazooka", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WMORTAR_SPRITE, "mortero", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WDYNIMITE_SPRITE, "dinamita", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WGGRENADE_SPRITE, "ggranada", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WRGRENADE_SPRITE, "rgranada", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WHOLY_SPRITE, "holy", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WRADIO_SPRITE, "radio", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WBAT_SPRITE, "bate", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WTELEPORT_SPRITE, "teleport", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WBANANA_SPRITE, "banana", screen.getRenderer());


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
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_BAZZOKA, "bullet_bazooka", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_MORTAR, "bullet_mortar", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_AIRMISL, "bullet_airmisl", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_DYNAMITE, "bullet_dynamite", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_HOLY, "bullet_holy", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_GGRENADE, "bullet_ggrenade", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_RGRENADE, "bullet_rgrenade", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BULLET_BANANA, "bullet_banana", this->getScreen().getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ FRAGMENT, "bullet_fragment", this->getScreen().getRenderer());

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
		TextureManager::Instance().load(_INSTALL_PATH_ VIGA, "viga", screen.getRenderer());

		//imagenes
		TextureManager::Instance().load(_INSTALL_PATH_ MSG_BOX, "message", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ WATCH, "reloj", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ SKY3, "sky3.png", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ TEXTURA1, "text1.png", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ TEXTURA2, "text2.png", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ TEXTURA3, "text3.png", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ TEXTURA4, "text4.png", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ TEXTURA5, "text5.png", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ TEXTURA6, "text6.png", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ MAREA1, "marea1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ MAREA2, "marea2", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ MAREA3, "marea3", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ MAREA4, "marea4", screen.getRenderer());

		// explosiones
		TextureManager::Instance().load(_INSTALL_PATH_ CIRCLE, "circle25", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ EXPLOTION_SPRITE, "explotion", screen.getRenderer());

		SpriteConfigurator::Instance().add("circle25", 50, 50, 8, false);
		SpriteConfigurator::Instance().add("explotion", 134, 134, 12, false);

		} catch (GameException & e) {
            std::cerr << e.what() << std::endl;
		}
}

void Boot::loadMenuWeapon(){
	try {

		TextureManager::Instance().load(_INSTALL_PATH_ MENU, "MenuWeapon", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ AIM, "aim", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ OK, "ok", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ BAZOOKA1, "bazooka.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BAZOOKA2, "bazooka.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ MORTAR1, "mortar.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ MORTAR2, "mortar.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ GGRENADE1, "g_grenade.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ GGRENADE2, "g_grenade.2", screen.getRenderer());
		
		TextureManager::Instance().load(_INSTALL_PATH_ RGRENADE1, "r_grenade.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ RGRENADE2, "r_grenade.2", screen.getRenderer());
		
		TextureManager::Instance().load(_INSTALL_PATH_ BANANA1, "banana.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BANANA2, "banana.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ HOLY1, "hgrenade.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ HOLY2, "hgrenade.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ DYNAMITE1, "dynamite.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ DYNAMITE2, "dynamite.2", screen.getRenderer());
	
		TextureManager::Instance().load(_INSTALL_PATH_ BASEBALL1, "baseball.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ BASEBALL2, "baseball.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ AIRSTRIKE1, "airstrke.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ AIRSTRIKE2, "airstrke.2", screen.getRenderer());

		TextureManager::Instance().load(_INSTALL_PATH_ TELEPORT1, "teleport.1", screen.getRenderer());
		TextureManager::Instance().load(_INSTALL_PATH_ TELEPORT2, "teleport.2", screen.getRenderer());

		/*inicia el manejo del texto*/
		TextManager::Instance().init(screen.getRenderer());
		TextManager::Instance().loadFont(Arial16);
		TextManager::Instance().loadFont(Arial12);

	} catch (GameException & e) {
		std::cout << e.what() << std::endl;	
	}
}

void Boot::loadSounds(){
	SoundManager::Instance().loadMusic(BACKGROUND, _INSTALL_PATH_ BACKGROUND_SOUND );
	SoundManager::Instance().loadSound(EXPLOTION, _INSTALL_PATH_ EXPLOTION_SOUND);
	SoundManager::Instance().loadSound(FUSE, _INSTALL_PATH_ FUSE_SOUND);
	SoundManager::Instance().loadSound(HOLY_S, _INSTALL_PATH_ HOLY_SOUND);
	SoundManager::Instance().loadSound(BANANA_S, _INSTALL_PATH_ BANANA_IMPACT_SOUND);
	SoundManager::Instance().loadSound(JUMP_S, _INSTALL_PATH_ JUMP_SOUND);
	SoundManager::Instance().loadSound(SHOOT, _INSTALL_PATH_ SHOOT_SOUND);
	SoundManager::Instance().loadSound(COMMUNICATOR, _INSTALL_PATH_ COMMUNICATOR_SOUND);
	SoundManager::Instance().loadSound(TELELEPORT_S, _INSTALL_PATH_ TELEPORT_SOUND);
	SoundManager::Instance().loadSound(BAT_IMPACT, _INSTALL_PATH_ BAT_IMPACT_SOUND);
	SoundManager::Instance().loadSound(BAT_JINGLE, _INSTALL_PATH_ BAT_JINGLE_SOUND);
	SoundManager::Instance().loadSound(BYE, _INSTALL_PATH_ BYEBYE_SOUND);
	SoundManager::Instance().loadSound(AIRSTRIKE, _INSTALL_PATH_ AIRSTRIKE_SOUND);
	SoundManager::Instance().loadSound(AIRSTRIKE, _INSTALL_PATH_ AIRSTRIKE_SOUND);
	SoundManager::Instance().loadSound(HELLO, _INSTALL_PATH_ HELLO_SOUND);
	SoundManager::Instance().loadSound(CURSOR_SELECT, _INSTALL_PATH_ CURSOR_SELECT_SOUND);
	SoundManager::Instance().loadSound(FIRE, _INSTALL_PATH_ FIRE_SOUND);
	SoundManager::Instance().loadSound(GRANADE, _INSTALL_PATH_ GRANADE_SOUND);
}

void Boot::loadFonts(){
	try{
		FontManager::Instance().openFont("arialbd", _INSTALL_PATH_ ARIAL_FONT, 12);
		FontManager::Instance().openFont("reloj", _INSTALL_PATH_ RELOJ_FONT, 11);
	} catch (SdlException& e){
		std::cout << e.what() << std::endl;	
	}
}

SdlScreen& Boot::getScreen(){
    return screen;
}