#include "Box2D/Box2D.h"
#include "multiple_proxy.h"
#include "gusano.h"
#include "viga.h"
#include <vector>
#include "util/yamlparser.h"
#include "delimiter.h"
#include <map>
#include "projectile.h"
#include "fragment_info.h"

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
		ObjectsFactory(b2World& world_e, MultipleProxy& proxy_e, 
		std::vector<std::pair<int, int>>& to_remove_gusanos_e, 
		GameConstants& info_e);
		
		~ObjectsFactory();
		
		void addTurnInfo(std::map<int, std::unique_ptr<Projectile>>* projectiles, 
					std::vector<int>* to_remove_projectiles_e, std::vector<FragmentInfo>* to_create);
		
		void createDelimiters(std::vector<Delimiter>& delimiters);
		
		void createViga(ElementInfo& information);
		
		void createGusano(std::vector<Gusano>& gusanos, ElementInfo& information);
		
		void createBazooka(int number, b2Vec2 position,
							int direction, float angle, float power);
							
		void createMorter(int number, b2Vec2 position,
							int direction, float angle, float power);
							
		void createGreenGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
		
		void createRedGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
						
		void createBanana(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
		
		void createSaintGranade(int number, b2Vec2 position,
						int direction, float angle, float power, unsigned int time);
						
		void createDynamite(int number, b2Vec2 position,
						int direction, unsigned int time);
						
		void createBat(Gusano& gusano, b2Vec2 position, int direction, float angle);
		
		void createAirAttackMissile(int number, float x);
		
		void createLittleProjectile(int number, FragmentInfo& information);
		
};

#endif
