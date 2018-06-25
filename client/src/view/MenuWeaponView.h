#ifndef __MENU_WEAPON_VIEW__
#define __MENU_WEAPON_VIEW__

#include "SdlScreen.h"
#include "WormStateAndWeapon.h"
#include "Weapon.h"
#include <map>
#include <list>

/*
* @class MenuWeaponView
* Es la vista del menu de armas
*/

class MenuWeaponView {
private:
	std::map<WeaponId, Weapon*> weapons;
	Weapon* menu;
	Camera& camera;
public:
	MenuWeaponView(Camera& camera);
	~MenuWeaponView();
	//construye el menu de armas
	void buildWeapon();
	//habilita o desabilita el menu de armas (estado inicial desabilitado)
	void actionMenu();
	//dibuja el menu solo si esta habilitado
	void draw(SdlScreen & screen);
	//agrega las armas al menu(armas en estado permitido)
	void allowWeapon(std::list<WeaponId> items);
	//verifica si se clickeo en el menu
	bool hasClickedMenu(SDL_Point clickPoint);
	//verifica si se clickeo en un arma
	bool hasClickedWeapon(SDL_Point clickPoint);
	//devulve la vista del arma que fue clickeada
	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);
	//Devuelve la vista del arma según el id
	Weapon* findWeaponById(WeaponId idWeapon);
};


#endif
