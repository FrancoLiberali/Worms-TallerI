#ifndef _WEAPON_H
#define _WEAPON_H

#include <list>
#include "WormStateAndWeapon.h"
#include "SdlScreen.h"
#include "Camera.h"
#include "Shape.h"
#include <SDL2/SDL.h>

/*
* @class Weapon
* Representa a un arma del menu de armas. 
*/
class Weapon {
private:
	std::list<std::string> lWeaponView;
	WeaponId id;
	std::string allowWeapon;
	int x, y, width, height;
	bool ballow;
	void drawItems(SdlScreen & screen);
public:
	Weapon(WeaponId id, Shape s, std::list<std::string> keys,std::string allowWeapon, Camera& camera);
	~Weapon();
	bool findWeapon(std::string key);
	WeaponId getId();
	Camera& camera;
	void setWeapon(std::string key);
	void setRender();
	void removeWeapon(std::string key);
	void draw(SdlScreen& screen);
	void allow();
	bool hasClickedMenu(SDL_Point clickPoint);
	void selected();
	void unSelected();
	void done();
};

#endif
