#ifndef __MENU_WEAPON_VIEW__
#define __MENU_WEAPON_VIEW__

#include "TextureManager.h"

#include "SdlScreen.h"
#include "WormStateAndWeapon.h"
#include "Weapon.h"
#include <map>
#include <list>

class MenuWeaponView {

private:
	std::map<WeaponId, Weapon*> weapons;
	Weapon* menu;
	Camera& camera;
public:
	MenuWeaponView(Camera& camera);
	~MenuWeaponView();
	void buildWeapon();
	void actionMenu();
	void offMenu();
	void draw(SdlScreen & screen);
	void allowWeapon(std::list<WeaponId> items);
	bool hasClickedMenu(SDL_Point clickPoint);
	bool hasClickedWeapon(SDL_Point clickPoint);
	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);
	Weapon* findWeaponById(WeaponId idWeapon);
	bool isOnAction();
};


#endif
