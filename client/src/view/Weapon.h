#ifndef _WEAPON_H
#define _WEAPON_H

#include <list>
#include "WormState.h"
#include "newView/SdlScreen.h"
#include "Shape.h"
#include <SDL2/SDL.h>

using namespace std;

class Weapon {

public:
	Weapon(WeaponId id, Shape s, list<string> keys, string allowWeapon);
	~Weapon();
	bool findWeapon(string key);
	WeaponId getId();
	void setWeapon(string key);
	void setRender();
	void removeWeapon(string key);
	void draw(SdlScreen& screen);
	void allow();
	bool hasClickedMenu(SDL_Point clickPoint);
	void selected();
	void unSelected();
private:
	list<string> lWeaponView;
	WeaponId id;
	string allowWeapon;
	int x, y, width, height;
	bool ballow;
	void drawItems(SdlScreen & screen);
};

#endif
