#ifndef _MAIN_View_H
#define _MAIN_View_H
#include "../controller/EventHandler.h"
#include "SdlScreen.h"
#include "Escenario.h"
#include "WormView.h"
#include "Camera.h"
#include "../controller/Event.h"
#include "BulletFactory.h"
#include "BulletView.h"
#include "PowerView.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

#include "MenuWeaponView.h"
#include "TextView.h"

class EventHandler;

/*Contiene todo referante al dibujado de los objetos*/
class mainView {
private:
	Escenario stage;

	SdlScreen& screen;
	Camera& camera;
	EventHandler& eventHandler;
	MenuWeaponView* menuWeapon;

	TextView turnView;

	std::map<int,WormView*> worms;
	std::map<int,BulletView*> bullets;

	bool open;
	bool endGame;
	int idPlayer;
	void init();
	void updateWorms();
	void updateBullets();
public:
	mainView(EventHandler& eventHandler, SdlScreen& screen, Camera& camera);
	~mainView();
	bool isOpen();
	void update();
	void close();
	void setIdPlayer(int idPlayer);
	WormView* getWormView(int id);
	BulletView* getBulletView(int id);
	SdlScreen& getScreen(){return screen;}
	void setMenuWeapon();
	void actionMenu();
	bool isMenuOn();
	bool hasClickedMenu(SDL_Point clickPoint);
	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);
	void addWorm(int id, int idOwner, std::string player, int x, int y, int dir, int angle);
	void addViga(int x, int y, int angle);
    void addMissile(int id, WeaponId weaponId, int dir, int posx, int posy, int angle);
	std::string changeTurn(std::string namePlayer, int idWorm);
	void showWinner();
	void showLosser();
	Camera& getCamera();

};

#endif
