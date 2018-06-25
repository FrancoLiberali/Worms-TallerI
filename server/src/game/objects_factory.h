#include "Box2D/Box2D.h"
#include "server/multiple_proxy.h"
#include "game/gusano/gusano.h"
#include "game/viga.h"
#include <vector>
#include "util/yamlparser.h"
#include "game/delimiter.h"
#include <map>
#include "game/weapons/projectile.h"
#include "game/weapons/fragment_info.h"

#ifndef __FACTORY_H__
#define __FACTORY_H__

class ObjectsFactory{
	private:
		b2World& world;
		MultipleProxy& proxy;
		std::vector<std::pair<int, int>>& to_remove_gusanos;
		GameConstants& info;
		std::map<int, std::unique_ptr<Projectile>>* projectiles;
		std::vector<int>* to_remove_projectiles;
		std::vector<FragmentInfo>* to_create;
		
	public:
		// Crea el objeto ObjectsFactory, el encargado
		// de crear todos los objetos fisicos del modelo.
		ObjectsFactory(b2World& world_e, MultipleProxy& proxy_e, 
		std::vector<std::pair<int, int>>& to_remove_gusanos_e, 
		GameConstants& info_e);
		
		~ObjectsFactory();
		
		// Agrega a la fabrica la informacion del objeto Turn
		// para crear proyectiles.
		void addTurnInfo(std::map<int, std::unique_ptr<Projectile>>* projectiles, 
					std::vector<int>* to_remove_projectiles_e, std::vector<FragmentInfo>* to_create);
		
		// Agrega el vector delimiters los cuatro delimitadores
		// del mapa segun el tamanio del mapa contenido en info.
		void createDelimiters(std::vector<Delimiter>& delimiters);
		
		// Crea una viga segun la informacion contenia en information.
		void createViga(ElementInfo& information);
		
		// Agrega a gusanos un gusano segun la informacion contenida
		// en information.
		void createGusano(std::vector<Gusano>& gusanos, ElementInfo& information);
		
		// Crea un proyectil bazooka.
		void createBazooka(int number, b2Vec2 position,
							int direction, float angle, float power);
		
		// Crea un proyectil mortero.				
		void createMorter(int number, b2Vec2 position,
							int direction, float angle, float power);
		
		// Crea un proyectil granada verde.		
		void createGreenGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
		
		// Crea un proyectil granada roja.
		void createRedGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
		
		// Crea un proyectil banana.
		void createBanana(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
		
		// Crea un proyectil granada santa.
		void createSaintGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
		
		// Crea un proyectil dinamita.				
		void createDynamite(int number, b2Vec2 position,
						int direction, unsigned int time);
		
		// Genera el efecto de un bateo ejecutado por gusano.				
		void createBat(Gusano& gusano, b2Vec2 position, int direction, float angle);
		
		// Crea un proyectil del ataque aereo en la posicion x y en el tope superior del mapa.
		void createAirAttackMissile(int number, float x);
		
		// Crea un pequenio proyectil causado por la explosion de un proyectil 
		// fragmentario segun la informacion contenida en information.
		void createLittleProjectile(int number, FragmentInfo& information);
		
};

#endif
