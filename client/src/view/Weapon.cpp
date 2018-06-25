#include "Weapon.h"
#include "../manager/TextureManager.h"
#include <algorithm>
#include <iostream>


Weapon::Weapon(WeaponId id, Shape s,std::list<std::string> keys,std::string allowWeapon, Camera& camera):
	camera(camera){
	std::pair<int, int> data;
	this->id = id;
	data = s.getPosition();
	this->x = data.first;
	this->y = data.second;
	data = s.getDimension();
	this->width = data.first;
	this->height = data.second;
	this->allowWeapon = allowWeapon;
	lWeaponView.insert(lWeaponView.begin(),keys.begin(),keys.end());
	ballow = false;
}

Weapon::~Weapon(){

}

void Weapon::setWeapon(std::string key){
	lWeaponView.push_back(key);
}

void Weapon::removeWeapon(std::string key){
	std::list<std::string>::iterator it;
	it = find(lWeaponView.begin(), 
		      lWeaponView.end(), key);
	if(it != lWeaponView.end()){
		lWeaponView.erase(it);
	}
}

bool Weapon::findWeapon(std::string key){
	std::list<std::string>::iterator it;
	it = find(lWeaponView.begin(), 
		      lWeaponView.end(), key);
	return (it != lWeaponView.end());
}

void Weapon::draw(SdlScreen& screen){
	drawItems(screen);
}

void Weapon::drawItems(SdlScreen & screen){
	std::list<std::string>::iterator it;
	for(it  = lWeaponView.begin();
		it != lWeaponView.end();
		it++){
		TextureManager::Instance().drawFrame(
					(*it), x, y, 0, width, height, 
					0, 0, screen.getRenderer(),
					false, SDL_FLIP_NONE);
	}

}

void Weapon::allow(){
	lWeaponView.push_back(allowWeapon);
	ballow = true;
}

bool Weapon::hasClickedMenu(SDL_Point clickPoint){
	int x1, x2, y1, y2;
	x1 = x, x2 = x + width;
	y1 = y, y2 = y + height;
	if((!ballow) && (this->id != NO_WEAPON))
		return false;
	if(
		((x1 <= clickPoint.x) && (x2 >= clickPoint.x))
		&&
		((y1 <= clickPoint.y) && (y2 >= clickPoint.y))
		){
			return true;
	}
	else{
		return false;
	}
}


WeaponId Weapon::getId(){
	return this->id;
}

void Weapon::selected(){
	if(!findWeapon("ok"))
		lWeaponView.push_back("ok");
}


void Weapon::unSelected(){
	if(findWeapon("ok"))
		removeWeapon("ok");
}

void Weapon::done(){
	this->removeWeapon(allowWeapon);
}