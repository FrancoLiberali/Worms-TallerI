#include "MenuWeaponView.h"
#include "newView/TextureManager.h"
#include <list>


#define WIDTH_WEAPON  32
#define HEIGHT_WEAPON 32
#define WIDTH_MENU_WEAPON 150
#define HEIGHT_MENU_WEAPON 70

MenuWeaponView::MenuWeaponView(){
}

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

void MenuWeaponView::draw(SdlScreen & screen){
	
	if(menu->findWeapon("MenuWeapon")){
		menu->draw(screen);
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			it->second->draw(screen);
		}
	}
}


void MenuWeaponView::allowWeapon(list<WeaponId> items){
	list<WeaponId>::iterator it;
	map<WeaponId, Weapon*>::iterator it2;

	for(it = items.begin();
		it != items.end();
		it++){
		it2 = mapa.find((*it));
		if(it2 != mapa.end()){
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
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
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
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			if(it->second->hasClickedMenu(clickPoint)){
				result = it->second;
				break;
			}
		}
	}
	return result;
}


void MenuWeaponView::buildWeapon(){
    
	int x, y, widthScreen, heightScreen;
	Shape *shape = NULL;
	list<string> lweapons;
	Weapon * weapon;

	widthScreen = TextureManager::Instance().getScreenWidth();
	heightScreen = TextureManager::Instance().getScreenHeight();

	x = widthScreen - WIDTH_MENU_WEAPON;
	y = HEIGHT_MENU_WEAPON;

	menu = new Weapon(NO_WEAPON,Shape(x,y,WIDTH_MENU_WEAPON,HEIGHT_MENU_WEAPON), lweapons, "");

	x += 1;	y += 2;
	lweapons.clear();
	lweapons.push_back("bazooka.2");
	weapon = new Weapon(BAZOOKA, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "bazooka.1");
	mapa.insert(pair<WeaponId, Weapon*>(BAZOOKA,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("mortar.2");
	weapon = new Weapon(MORTERO, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "mortar.1");
	mapa.insert(pair<WeaponId, Weapon*>(MORTERO,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("g_grenade.2");
	weapon = new Weapon(G_GRENADE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "g_grenade.1");
	mapa.insert(pair<WeaponId, Weapon*>(G_GRENADE,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("r_grenade.2");
	weapon = new Weapon(R_GRENADE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "r_grenade.1");
	mapa.insert(pair<WeaponId, Weapon*>(R_GRENADE,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("banana.2");
	weapon = new Weapon(BANANA, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "banana.1");
	mapa.insert(pair<WeaponId, Weapon*>(BANANA,weapon));

	x  = widthScreen - WIDTH_MENU_WEAPON + 1;
	y  += HEIGHT_WEAPON;
	lweapons.clear();
	lweapons.push_back("hgrenade.2");
	weapon = new Weapon(HOLY, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "hgrenade.1");
	mapa.insert(pair<WeaponId, Weapon*>(HOLY,weapon));

	x += WIDTH_WEAPON - 2;
	lweapons.clear();
	lweapons.push_back("dynamite.2");
	weapon = new Weapon(DYNAMITE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "dynamite.1");
	mapa.insert(pair<WeaponId, Weapon*>(DYNAMITE,weapon));

	x += WIDTH_WEAPON - 3;
	lweapons.clear();
	lweapons.push_back("baseball.2");
	weapon = new Weapon(BATE, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "baseball.1");
	mapa.insert(pair<WeaponId, Weapon*>(BATE,weapon));

	x += WIDTH_WEAPON - 3;
	//y = y - 5;
	lweapons.clear();
	lweapons.push_back("airstrke.2");
	weapon = new Weapon(AIRATTACK, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "airstrke.1");
	mapa.insert(pair<WeaponId, Weapon*>(AIRATTACK,weapon));

	x += WIDTH_WEAPON - 3;
	//y += 5;
	lweapons.clear();
	lweapons.push_back("teleport.2");
	weapon = new Weapon(TELEPORT, Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON), lweapons, "teleport.1");
	mapa.insert(pair<WeaponId, Weapon*>(TELEPORT,weapon));

}

