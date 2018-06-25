#include "MenuWeaponView.h"
#include "../manager/TextureManager.h"
#include "../manager/SoundManager.h"

#include <list>

#define WIDTH_WEAPON  32
#define HEIGHT_WEAPON 32
#define WIDTH_MENU_WEAPON 150
#define HEIGHT_MENU_WEAPON 70

MenuWeaponView::MenuWeaponView(Camera& camera):camera(camera){}

MenuWeaponView::~MenuWeaponView(){
}

void MenuWeaponView::actionMenu(){
	if(menu->findWeapon("MenuWeapon")){
		menu->removeWeapon("MenuWeapon");
	}
	else{
		menu->setWeapon("MenuWeapon");
	}
}

void MenuWeaponView::draw(SdlScreen& screen){
	if(menu->findWeapon("MenuWeapon")){
		menu->draw(screen);
		std::map<WeaponId, Weapon*>::iterator it;
		for(it = weapons.begin(); it != weapons.end(); it++){
			it->second->draw(screen);
		}
	}
}



void MenuWeaponView::allowWeapon(std::list<WeaponId> items){
	std::list<WeaponId>::iterator it;
	std::map<WeaponId, Weapon*>::iterator it2;
	for(it = items.begin(); it != items.end(); it++){
		it2 = weapons.find((*it));
		if(it2 != weapons.end()){
			it2->second->allow();
		}
	}
}

bool MenuWeaponView::hasClickedMenu(SDL_Point clickPoint){
	bool result = false;
	if(menu->findWeapon("MenuWeapon")
	&& (menu->hasClickedMenu(clickPoint))){
		result = true;
	}
	return result;
}

bool MenuWeaponView::hasClickedWeapon(SDL_Point clickPoint){
	bool result = false;
	if(menu->findWeapon("MenuWeapon")){
		SoundManager::Instance().playSound(CURSOR_SELECT);
		std::map<WeaponId, Weapon*>::iterator it;
		for(it = weapons.begin(); it != weapons.end(); it++){
			if(it->second->hasClickedMenu(clickPoint)){
				result = true;
				break;
			}
		}
	}
	return result;
}


Weapon* MenuWeaponView::retrieveWeaponClicked(SDL_Point clickPoint){
	Weapon* result = NULL;
	if(menu->findWeapon("MenuWeapon")){
		SoundManager::Instance().playSound(CURSOR_SELECT);
		std::map<WeaponId, Weapon*>::iterator it;
		for(it = weapons.begin(); it != weapons.end(); it++){
			if(it->second->hasClickedMenu(clickPoint)){
				result = it->second;
				break;
			}
		}
	}
	return result;
}

Weapon* MenuWeaponView::findWeaponById(WeaponId idWeapon){
	return this->weapons[idWeapon];
}

void MenuWeaponView::buildWeapon(){
    
	int x, y, widthScreen, heightScreen;
	Shape *shape = NULL;
	std::list<std::string> lweapons;
	Weapon* weapon;

	widthScreen = TextureManager::Instance().getScreenWidth();
	heightScreen = TextureManager::Instance().getScreenHeight();

	x = widthScreen - WIDTH_MENU_WEAPON;
	y = HEIGHT_MENU_WEAPON;

	menu = new Weapon(NO_WEAPON,Shape(x,y,WIDTH_MENU_WEAPON,HEIGHT_MENU_WEAPON), lweapons, "", camera);

	x += 1;	y += 2;
	lweapons.clear();
	lweapons.push_back("bazooka.2");
	weapon = new Weapon(BAZOOKA, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "bazooka.1", camera);
	weapons.emplace(BAZOOKA, weapon);

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("mortar.2");
	weapon = new Weapon(MORTERO, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "mortar.1", camera);
	weapons.emplace(MORTERO, weapon);

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("g_grenade.2");
	weapon = new Weapon(G_GRENADE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "g_grenade.1", camera);
	weapons.emplace(G_GRENADE, weapon);

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("r_grenade.2");
	weapon = new Weapon(R_GRENADE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "r_grenade.1", camera);
	weapons.emplace(R_GRENADE, weapon);

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("banana.2");
	weapon = new Weapon(BANANA, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "banana.1", camera);
	weapons.emplace(BANANA, weapon);

	x  = widthScreen - WIDTH_MENU_WEAPON + 1;
	y  += HEIGHT_WEAPON;
	lweapons.clear();
	lweapons.push_back("hgrenade.2");
	weapon = new Weapon(HOLY, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "hgrenade.1", camera);
	weapons.emplace(HOLY, weapon);

	x += WIDTH_WEAPON - 2;
	lweapons.clear();
	lweapons.push_back("dynamite.2");
	weapon = new Weapon(DYNAMITE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "dynamite.1", camera);
	weapons.emplace(DYNAMITE, weapon);

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("baseball.2");
	weapon = new Weapon(BATE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "baseball.1", camera);
	weapons.emplace(BATE, weapon);

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("airstrke.2");
	weapon = new Weapon(AIRATTACK, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "airstrke.1", camera);
	weapons.emplace(AIRATTACK, weapon);

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("teleport.2");
	weapon = new Weapon(TELEPORT, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "teleport.1", camera);
	weapons.emplace(TELEPORT,weapon);

}

