#include "objects_factory.h"
#include "bazooka.h"
#include "morter.h"
#include "green_granade.h"
#include "red_granade.h"
#include "banana.h"
#include "saint_granade.h"
#include "dynamite.h"
#include "bat.h"
#include "air_attack_missile.h"
#include <cmath>

#define MAP_OFFSET 25
#define WATER_DEPPNESS 3
#define LEFT_AND_RIGHT 2
#define TOP_LIMIT 0
#define LEFT_LIMIT 0
#define LEFT -1

#define WORM_HEIGHT 0.6

ObjectsFactory::ObjectsFactory(b2World& world_e, MultipleProxy& proxy_e, 
	std::vector<std::pair<int, int>>& to_remove_gusanos_e, GameConstants& info_e) :
		world(world_e), proxy(proxy_e), to_remove_gusanos(to_remove_gusanos_e), 
		info(info_e){
}

ObjectsFactory::~ObjectsFactory(){
}

void ObjectsFactory::addTurnInfo(std::map<int, std::unique_ptr<Projectile>>* projectiles_e, 
					std::vector<int>* to_remove_projectiles_e, std::vector<FragmentInfo*>* to_create_e){
	this->projectiles = projectiles_e;
	this->to_remove_projectiles = to_remove_projectiles_e;
	this->to_create = to_create_e;
}

void ObjectsFactory::createDelimiters(std::vector<Delimiter>& delimiters){
	//se agregan al mapa espacios vacios a izquierda, derecha y arriba, y abajo un pequenio espacio para el agua
	float down_limit = info.map_height + WATER_DEPPNESS + MAP_OFFSET;
	float right_limit = info.map_widht + LEFT_AND_RIGHT * MAP_OFFSET;
	this->proxy.sendMapDimentions(right_limit, down_limit);
	
	delimiters.push_back(std::move(Delimiter(this->world, LEFT_LIMIT, TOP_LIMIT, LEFT_LIMIT, -down_limit))); //left
	delimiters.push_back(std::move(Delimiter(this->world, LEFT_LIMIT, TOP_LIMIT, right_limit, TOP_LIMIT)));//top
	delimiters.push_back(std::move(Delimiter(this->world, right_limit, 
									TOP_LIMIT, right_limit, -down_limit)));//right
	delimiters.push_back(std::move(Delimiter(this->world, LEFT_LIMIT, -down_limit, 
							right_limit, -down_limit)));//botton
}

void ObjectsFactory::createViga(ElementInfo& information){
	//las coordenas del y se ponen negativas para que el mundo se encuentre en el 4 cuadrante, para que su espacio
	// sea similar al dibujable por el client
	Viga viga(this->world, information.x + MAP_OFFSET, -information.y - MAP_OFFSET, information.angulo, this->proxy);
}

void ObjectsFactory::createGusano(std::vector<Gusano>& gusanos, ElementInfo& information){
	//las coordenas del y se ponen negativas para que el mundo se encuentre en el 4 cuadrante, para que su espacio
	// sea similar al dibujable por el client
	Gusano gusano(this->world, this->proxy, this->to_remove_gusanos,
			information.x + MAP_OFFSET, -information.y - MAP_OFFSET, information.angulo, this->info.worms_life);
	gusanos.push_back(std::move(gusano));
}

void ObjectsFactory::createBazooka(int number, b2Vec2 position,
						int direction, float angle, float power){
	//la posicion varia de la recibida porque la misma es la posicion del 
	//gusano que dispara, y se debe mover para que quede fuera de el.
	// el angulo cambia ya que el angulo se encuentra medido desde la horizontal
	// en la direccion del disparo, por lo que cuando se dispara a la izquierda
	// se debe restar el angulo a 180 grados
	Bazooka* bazooka = new Bazooka(this->world, number, 
						position.x + (WORM_HEIGHT + this->info.bazooka_widht) * cos(angle) * direction, 
						position.y + (WORM_HEIGHT + this->info.bazooka_widht) * sin(angle), direction, 
						(direction == LEFT)? M_PI-angle : angle, power, this->info, 
						*(this->to_remove_projectiles), this->proxy);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(bazooka)));
}

void ObjectsFactory::createMorter(int number, b2Vec2 position,
						int direction, float angle, float power){
	Morter* morter = new Morter(this->world, number, 
						position.x + (WORM_HEIGHT + this->info.morter_widht) * cos(angle) * direction, 
						position.y + (WORM_HEIGHT + this->info.morter_widht) * sin(angle), direction, 
						(direction == LEFT)? M_PI-angle : angle, power, this->info, 
						*(this->to_remove_projectiles), *(this->to_create), this->proxy);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(morter)));
}



void ObjectsFactory::createGreenGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time){
	GreenGranade* green = new GreenGranade(this->world, number, 
						position.x + (WORM_HEIGHT + this->info.green_granade_widht) * cos(angle) * direction, 
						position.y + (WORM_HEIGHT + this->info.green_granade_widht) * sin(angle), direction, 
						(direction == LEFT)? M_PI-angle : angle, power, this->info, 
						*(this->to_remove_projectiles), this->proxy, time);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(green)));
}

void ObjectsFactory::createRedGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time){
	RedGranade* red = new RedGranade(this->world, number, 
						position.x + (WORM_HEIGHT + this->info.red_granade_widht) * cos(angle) * direction, 
						position.y + (WORM_HEIGHT + this->info.red_granade_widht) * sin(angle), direction, 
						(direction == LEFT)? M_PI-angle : angle, power, this->info, 
						*(this->to_remove_projectiles), *(this->to_create), this->proxy, time);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(red)));
}

void ObjectsFactory::createBanana(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time){
	Banana* banana = new Banana(this->world, number, 
						position.x + (WORM_HEIGHT + this->info.banana_widht) * cos(angle) * direction, 
						position.y + (WORM_HEIGHT + this->info.banana_widht) * sin(angle), direction, 
						(direction == LEFT)? M_PI-angle : angle, power, this->info, 
						*(this->to_remove_projectiles), this->proxy, time);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(banana)));
}

void ObjectsFactory::createSaintGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time){
	SaintGranade* saint = new SaintGranade(this->world, number, 
						position.x + (WORM_HEIGHT + this->info.saint_granade_widht) * cos(angle) * direction, 
						position.y + (WORM_HEIGHT + this->info.saint_granade_widht) * sin(angle), direction, 
						(direction == LEFT)? M_PI-angle : angle, power, this->info, 
						*(this->to_remove_projectiles), this->proxy, time);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(saint)));
}

void ObjectsFactory::createDynamite(int number, b2Vec2 position,
						int direction, unsigned int time){
	Dynamite* dynamite = new Dynamite(this->world, number, 
						position.x + (WORM_HEIGHT + this->info.dynamite_widht) * direction, 
						position.y, direction, 
						this->info, *(this->to_remove_projectiles), this->proxy, time);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(dynamite)));
}

void ObjectsFactory::createBat(Gusano& gusano, b2Vec2 position, int direction, float angle){
	Bat(gusano, this->world, position.x, position.y, direction, angle, this->info);
}

void ObjectsFactory::createAirAttackMissile(int number, float x){
	AirAttackMissile* missile = new AirAttackMissile(this->world, number, 
						x, this->info, *(this->to_remove_projectiles), this->proxy);
	this->projectiles->insert(std::pair<int, std::unique_ptr<Projectile>>(number, 
						std::unique_ptr<Projectile>(missile)));
}
