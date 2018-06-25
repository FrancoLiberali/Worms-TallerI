#ifndef _WEAPON_H
#define _WEAPON_H

#include <list>
#include "WormStateAndWeapon.h"
#include "SdlScreen.h"
#include "Camera.h"
#include "Shape.h"
#include <SDL2/SDL.h>

using namespace std;

class Weapon {

public:
	Weapon(WeaponId id, Shape s, list<string> keys, string allowWeapon, Camera& camera);
	~Weapon();
	bool findWeapon(string key);
	WeaponId getId();
	Camera& camera;
	void setWeapon(string key);
	void setRender();
	void removeWeapon(string key);
	void draw(SdlScreen& screen);
	void allow();
	bool hasClickedMenu(SDL_Point clickPoint);
	void selected();
	void unSelected();
	void done();
private:
	list<string> lWeaponView;
	WeaponId id;
	string allowWeapon;
	int x, y, width, height;
	bool ballow;
	void drawItems(SdlScreen & screen);
};

#endif
