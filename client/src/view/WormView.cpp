#include "WormView.h"
#include <iostream>

WormView::WormView(int idWorm, int idOwner, Camera& camera)
	:flip(SDL_FLIP_NONE), camera(camera){
	this->idOwner = idOwner;
	this->state = STATIC;
	currentSprite = NULL;
	this->selected = true;
	this->weaponId = NO_WEAPON;
	this->widhtLife100 = 25;
	this->widhtLifeCurrent = 25;
	this->currentLife = 100;
	this->alive = true;
	this->focus = false;
}


/*optinizar esto*/
SDL_Color getColor(int id){
	switch (id){
		case 1:{
			SDL_Color color = {255,0,0};
			return color;
		}
		case 2:{
			SDL_Color color = {0,0,255};
			return color;
		}
		case 3:{
			SDL_Color color = {0,255,0};
			return color;
		}
		case 4:{
			SDL_Color color = {153,102,0};
			return color;
		}
	}
}

void WormView::load(int x, int y, SdlScreen* screen){
	this->setPos(x, y);
	this->screen = screen;
	this->aim.setScreen(screen);
	//Cargamos los sprites
	try {
		sprites["caminar"] = SpriteConfigurator::Instance().get("caminar");
		sprites["saltar"] = SpriteConfigurator::Instance().get("saltar");
		sprites["morir"] = SpriteConfigurator::Instance().get("morir");
		sprites["cripta"] = SpriteConfigurator::Instance().get("cripta");
		sprites["explosion"] = SpriteConfigurator::Instance().get("circle25");

		sprites["bazooka"] = SpriteConfigurator::Instance().get("bazooka");
		sprites["dinamita"] = SpriteConfigurator::Instance().get("dinamita");
		sprites["ggranada"] = SpriteConfigurator::Instance().get("ggranada");
		sprites["rgranada"] = SpriteConfigurator::Instance().get("rgranada");
		sprites["holy"] = SpriteConfigurator::Instance().get("holy");
		sprites["radio"] = SpriteConfigurator::Instance().get("radio");
		sprites["bate"] = SpriteConfigurator::Instance().get("bate");
		sprites["banana"] = SpriteConfigurator::Instance().get("banana");
		sprites["bate"] = SpriteConfigurator::Instance().get("bate");
		sprites["mortero"] = SpriteConfigurator::Instance().get("mortero");
		sprites["teleport"] = SpriteConfigurator::Instance().get("teleport");
	
	} catch (std::exception & e) {
		std::cout<<e.what()<<std::endl;
		return;
	}
	this->update();
}

void WormView::setPos(int x, int y){
	this->x = x; this->y = y;
	aim.setCenter(x,y);
	if (focus)
		camera.updateCenter(this->getXCenter(), this->getYCenter());
}

void WormView::setPlayerName(std::string player){
	SDL_Color black = {255,255,255};
	labelUsuario.setText(player, black);
}


void WormView::update(){
	if (currentSprite == NULL) {
		currentSprite = &this->sprites["caminar"];
		aim.disable();
	}
	if (this->state == JUMP){
		// Camino sin arma
		if (currentSprite != &this->sprites["saltar"])
			currentSprite = &this->sprites["saltar"];
		currentSprite->update();
		aim.disable();
	} else if (this->state == MOVE){
		// Camino sin arma
		if (currentSprite != &this->sprites["caminar"])
			currentSprite = &this->sprites["caminar"];
		currentSprite->update();
		aim.disable();
	} 
	else if (this->state == STATIC){
		if (this->weaponId == G_GRENADE && currentSprite != &this->sprites["ggranada"]){
			currentSprite = &this->sprites["ggranada"];
			aim.enable();
		}
		if (this->weaponId == R_GRENADE && currentSprite != &this->sprites["rgranada"]){
			currentSprite = &this->sprites["rgranada"];
			aim.enable();
		}
		if (this->weaponId == DYNAMITE && currentSprite != &this->sprites["dinamita"]){
			currentSprite = &this->sprites["dinamita"];
			aim.enable();
		}
		if (this->weaponId == BAZOOKA && currentSprite != &this->sprites["bazooka"]){
			currentSprite = &this->sprites["bazooka"];
			aim.enable();
		}
		if (this->weaponId == BANANA && currentSprite != &this->sprites["banana"]){
			currentSprite = &this->sprites["banana"];
			aim.enable();
		}
		if (this->weaponId == MORTERO && currentSprite != &this->sprites["mortero"]){
			currentSprite = &this->sprites["mortero"];
			aim.enable();
		}
		if (this->weaponId == HOLY && currentSprite != &this->sprites["holy"]){
			currentSprite = &this->sprites["holy"];
			aim.enable();
		}
		if (this->weaponId == AIRATTACK && currentSprite != &this->sprites["radio"]){
			currentSprite = &this->sprites["radio"];
			aim.disable();
		}
		if (this->weaponId == BATE && currentSprite != &this->sprites["bate"]){
			currentSprite = &this->sprites["bate"];
			aim.enable();
		}
		if (this->weaponId == TELEPORT && currentSprite != &this->sprites["teleport"]){
			currentSprite = &this->sprites["teleport"];
			aim.disable();
		}
		if (this->weaponId == NO_WEAPON && currentSprite != &this->sprites["caminar"]){
			currentSprite = &this->sprites["caminar"];
			aim.disable();
		}
		currentSprite->clean();

	} else if (this->state == DEAD) {
	
		////std::cout<<"WormView::update >> sprite worm morir"<<std::endl;
		if (alive)
			currentSprite = &this->sprites["morir"];

		if (currentSprite == &this->sprites["morir"] && currentSprite->isLastFrame())
			currentSprite = &this->sprites["explosion"];

		alive = false;
		currentSprite->update();
	}
	draw();
}


void WormView::draw(){
	
	TextureManager::Instance().drawFrame(currentSprite->getImageId(),
									getXCenter(),getYCenter(), angle, 
									currentSprite->getWidth(),
									currentSprite->getHeight(),
									currentSprite->getCurrentRow(),
									currentSprite->getCurrentFrame(),
									screen->getRenderer(),false,flip);
	 
	if (this->selected)
		labelUsuario.draw(screen->getRenderer(),this->getXCenter()-camera.getX(),  this->getYCenter()-camera.getY()- 15);
 
	aim.draw();

	SDL_Rect rect;
	rect.x = this->getX()-camera.getX() - 10;
	rect.y = this->getY()-camera.getY() - 22;
	rect.w = this->widhtLifeCurrent;
	rect.h = 5;
	SDL_Color color = getColor(idOwner);
	TextureManager::Instance().drawFillRect(screen->getRenderer(),rect, color);
}

void WormView::selectWeapon(WeaponId idWapon){
	this->weaponId = idWapon;
}


WormView::~WormView(){
}

void WormView::changeState(WormState newState){
	if (this->state == newState)
		return;
	this->state = newState;
}

void WormView::setDirection(int dir){
	SDL_RendererFlip currFlip = (dir == 1)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	
	if (flip != currFlip)
		aim.changeDir();
	
	flip = currFlip;
}
void WormView::setAngle(int angle){
	this->angle = angle;
}

int WormView::getXCenter()
{
	return this->getX()-(currentSprite->getWidth()/2);
}

int WormView::getX(){
	return this->x;
}

int WormView::getY(){
	return this->y;
}

int WormView::getYCenter()
{
	return this->getY()-(currentSprite->getHeight()/2);
}

void WormView::changeLife(int newLife){
	int widhtLifeCurrent = newLife * widhtLife100 /100;
	currentLife = newLife;
}

void WormView::changeAimAngle(int delta){
	aim.changeAngle(delta);
}

void WormView::onFocus(){
	focus = true;
}

void WormView::offFocus(){
	focus = false;
}
