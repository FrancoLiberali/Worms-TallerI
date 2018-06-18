#include "Boot.h"

#include "TextureManager.h"
#include "TextManager.h"
#include "SpriteConfigurator.h"
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
    loadSprites();
	loadMenuWeapon();
	initCamera(0,0);
}

void Boot::reinit(){}

void Boot::loadConfigGame(){

}

void Boot::loadSprites(){
	try {
		// worm
		TextureManager::Instance().load("../resource/images/wwalk.png", "caminar", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wdie.png", "morir", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wflyup.png", "saltar", screen.getRenderer());
		
		TextureManager::Instance().load("../resource/images/grave2.png", "cripta", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wstatic.png", "static", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wbaz.png", "bazooka", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wbaz.png", "mortero", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wdynbak.png", "dinamita", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wthrgrn.png", "ggranada", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wthrcls.png", "rgranada", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wthrhgr.png", "holy", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wairbak.png", "radio", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wbsbaim.png", "bate", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wtelbak.png", "teleport", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/wthrban.png", "banana", screen.getRenderer());


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

		TextureManager::Instance().load("../resource/images/misiles/bazzoka.png", "bullet_bazooka", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/mortar.png", "bullet_mortar", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/airmisl.png", "bullet_airmisl", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/dynamite.png", "bullet_dinamita", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/hgrenade.png", "bullet_holy", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/ggrenade.png", "bullet_ggrenade", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/rgrenade.png", "bullet_rgrenade", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/banana.png", "bullet_banana", this->getScreen().getRenderer());
		TextureManager::Instance().load("../resource/images/misiles/fragment.png", "bullet_fragment", this->getScreen().getRenderer());

		SpriteConfigurator::Instance().add("bullet_airmisl", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_dinamita", 60, 60, 129, true);
		SpriteConfigurator::Instance().add("bullet_holy", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_ggrenade", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_rgrenade", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_bazooka", 60, 60, 32, true, 23);
		SpriteConfigurator::Instance().add("bullet_mortar", 60, 60, 32, true, 23);
		SpriteConfigurator::Instance().add("bullet_banana", 60, 60, 32, true);
		SpriteConfigurator::Instance().add("bullet_fragment", 60, 60, 6, true);
		
		//Vigas
		TextureManager::Instance().load("../resource/images/vigah.png", "viga", screen.getRenderer());

		//imagenes
		TextureManager::Instance().load("../resource/images/sky.png", "sky",screen.getRenderer());
		TextureManager::Instance().load("../resource/images/win.png", "win", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/lose.png", "lose", screen.getRenderer());

		// explosiones
		TextureManager::Instance().load("../resource/images/circle25.png", "circle25", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/explotion.png", "explotion", screen.getRenderer());

		SpriteConfigurator::Instance().add("circle25", 50, 50, 8, false);
		SpriteConfigurator::Instance().add("explotion", 134, 134, 12, false);

		} catch (GameException & e) {
            std::cerr << e.what() << std::endl;
		}
	////std::cout << "Se cargaron todas las texturas" << std::endl;
}
void Boot::loadImages(){}
void Boot::loadWaterImage(){}
void Boot::loadEart(){}

void Boot::loadMenuWeapon(){
	try {

		TextureManager::Instance().load("../resource/images/menuWeapon/MenuWeapon.png", "MenuWeapon", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/aim.png", "aim", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/ok.png", "ok", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/bazooka.1.png", "bazooka.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/bazooka.2.png", "bazooka.2", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/mortar.1.png", "mortar.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/mortar.2.png", "mortar.2", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/grenade.1.png", "g_grenade.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/grenade.2.png", "g_grenade.2", screen.getRenderer());
		
		TextureManager::Instance().load("../resource/images/menuWeapon/cluster.1.png", "r_grenade.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/cluster.2.png", "r_grenade.2", screen.getRenderer());
		
		TextureManager::Instance().load("../resource/images/menuWeapon/banana.1.png", "banana.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/banana.2.png", "banana.2", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/hgrenade.1.png", "hgrenade.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/hgrenade.2.png", "hgrenade.2", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/dynamite.1.png", "dynamite.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/dynamite.2.png", "dynamite.2", screen.getRenderer());
	
		TextureManager::Instance().load("../resource/images/menuWeapon/baseball.1.png", "baseball.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/baseball.2.png", "baseball.2", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/airstrke.1.png", "airstrke.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/airstrke.2.png", "airstrke.2", screen.getRenderer());

		TextureManager::Instance().load("../resource/images/menuWeapon/teleport.1.png", "teleport.1", screen.getRenderer());
		TextureManager::Instance().load("../resource/images/menuWeapon/teleport.2.png", "teleport.2", screen.getRenderer());

		/*inicia el manejo del texto*/
		TextManager::Instance().init(screen.getRenderer());
		TextManager::Instance().loadFont(Arial16);
		TextManager::Instance().loadFont(Arial12);

	} catch (GameException & e) {
		////std::cout << e.what() << std::endl;	
	}

	////std::cout << "Se cargo el menu" << std::endl;

}

void Boot::initCamera(int x, int y){
	int widht = screen.getWidth();
	int height = screen.getHeight();
	//TextureManager::Instance().getCamera().setDimension(widht, height);
}
void Boot::realoadEart(){}

SdlScreen& Boot::getScreen(){
    return screen;
}
