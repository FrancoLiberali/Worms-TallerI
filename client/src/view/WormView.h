#ifndef _WORM_VIEW_
#define _WORM_VIEW_ 

#include "newView/SdlScreen.h"
#include "WormState.h"
#include "newView/Sprite.h"
#include "newView/SpriteConfigurator.h"
#include "newView/TextureManager.h"
#include "newView/TextView.h"
#include "AimView.h"

#include <map>

class WormView {
private:
	SdlScreen* screen;
	int id, x, y, angle;
	SDL_RendererFlip flip;

	WormState state;

	Sprite* currentSprite;
	std::map<std::string, Sprite> sprites;

	int currentLife;
	int widhtLife100;
	int widhtLifeCurrent;

	WeaponId weaponId;
	AimView aim;

	bool selected;

	SDL_Color white;

	bool alive;
	TextView labelUsuario;
	int idOwner;

	void draw();
	int getXCenter();
	int getYCenter();
public:
	WormView(int idWorm, int idOwner);
	void setPlayerName(std::string player);
	~WormView();
	void selectWeapon(WeaponId idWapon);
	void unselectWeapon() {this->weaponId = NO_WEAPON;}
	void load(int x, int y, SdlScreen* window);
	void setPos(int x, int y);
	int getX();
	int getY();
	void update();
	void changeState(WormState newState);
	void setDirection(int dir);
	void setAngle(int angle);
	void changeLife(int newLife);
	void changeAimAngle(int delta);
};

#endif