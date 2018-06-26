#ifndef _MAIN_View_H
#define _MAIN_View_H
#include "../controller/EventHandler.h"
#include "SdlScreen.h"
#include "Escenario.h"
#include "WormView.h"
#include "Camera.h"
#include "bullets/BulletFactory.h"
#include "bullets/BulletView.h"
#include "PowerView.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

#include "MenuWeaponView.h"
#include "TextView.h"
#include "PanelInfo.h"
#include "WatchView.h"

class EventHandler;

/*
* @class mainView
* clase principal de la vista del cliente, contiene referencia a todas las vistas.
*/
class mainView {
private:
	Escenario stage;

	SdlScreen& screen;
	Camera& camera;
	EventHandler& eventHandler;
	MenuWeaponView* menuWeapon;

	PanelInfo panelInfo;
	WatchView watch;

	std::map<int,WormView*> worms;
	std::map<int,BulletView*> bullets;

	bool open;
	bool endGame;
	int idPlayer;
	void init();
	void updateItems();
public:
	mainView(EventHandler& eventHandler, SdlScreen& screen, Camera& camera);
	~mainView();
	//metodos que describen el estado de la ventana
	void close();
	void openWindow();
	bool isOpen();

	//actualiza y dibuja todos las vistas
	void update();

	//metodos de manupalicion del menu de armas
	void actionMenu();	;
	bool hasClickedMenu(SDL_Point clickPoint);
	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);

	//agregar elementos a la vista
	void addWorm(int id, int idOwner, std::string& player, int x, int y, int dir, int angle);
	void addViga(int x, int y, int angle);
    void addMissile(int id, WeaponId weaponId, int dir, int posx, int posy, int angle);

	//mensajes que cambia la vista
	std::string changeTurn(std::string& namePlayer, int idWorm);
	void showLosser(int idPlayer, std::string& name);
	void WormShoot(int idWorm);
	void createStage(int widht, int height);
	void setBackground(std::string name);
	void weaponDone(WeaponId id);
	void second();
	void windChanged(int speed);

	//geters
	WormView* getWormView(int id);
	BulletView* getBulletView(int id);
	SdlScreen& getScreen(){return screen;}
	Camera& getCamera();
};

#endif
