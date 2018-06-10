#ifndef _MAIN_View_H
#define _MAIN_View_H
#include "../controller/EventHandler.h"
#include "newView/SdlScreen.h"
#include "Escenario.h"
#include "WormView.h"
#include "../controller/Event.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

#include "MenuWeaponView.h"

class EventHandler;

/*Contiene todo referante al dibujado de los objetos*/
class mainView {
private:
	Escenario stage;

	SdlScreen& screen;
	EventHandler& eventHandler;
	WormView* worm;
	MenuWeaponView* menuWeapon;

	std::map<int,WormView*> worms;
	bool open;
	void procesar(std::string mensaje);
	void init();
public:
	mainView(EventHandler& eventHandler, SdlScreen& screen);
	~mainView();
	bool isOpen();
	void update();
	void close();
	//para pruebas
	WormView* getWormView(int id);
	SdlScreen& getScreen(){return screen;}
	void setMenuWeapon();
	void actionMenu();
	bool isMenuOn();
	bool hasClickedMenu(SDL_Point clickPoint);
	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);
	void addWorm(int id, std::string player, int x, int y, int dir, int angle);
	void addViga(int x, int y, int angle);
	std::string changeTurn(std::string namePlayer);
};

#endif
