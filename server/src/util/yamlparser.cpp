#include "util/yamlparser.h"
#include "game_constants.h"
#include <iostream>

#define INF_VALUE -1
#define INFINITO "infinitas"
#define BANANA "Banana"
#define BAZOOKA "Bazooka"
#define MORTERO "Mortero"
#define TELETRANSPORTACION "Teletransportacion"
#define GRANADA_VERDE "Granada Verde"
#define GRANADA_ROJA "Granada Roja"
#define GRANADA_SANTA "Granada Santa"
#define DINAMITA "Dinamita"
#define BATE "Bate de Baseball"
#define ATAQUE_AEREO "Ataque Aereo"

YAMLParser::YAMLParser() {}

void YAMLParser::cargarConfig(const std::string& name, std::vector<ElementInfo>& v, GameConstants& info)
{
	std::cout << name << "\n";
    YAML::Node config = YAML::LoadFile("../maps/" + name);
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it){
        std::string key(it->first.as<std::string>());
        if (key.compare("armas") == 0){
            cargarArmas(it->second, info);
        }
        if (key.compare("objetos") == 0){
            cargarMapa(it->second, v, info);
        }
        if (key.compare("metadata") == 0){
			for(YAML::const_iterator it2 = it->second.begin(); it2!=it->second.end(); ++it2){
				std::string key2(it2->first.as<std::string>());
				if (key2.compare("ancho") == 0){
					info.map_widht = it2->second.as<float>();
				}
				if (key2.compare("alto") == 0){
					info.map_height = it2->second.as<float>();
				}
				if (key2.compare("fondo") == 0){
					info.map_background = it2->second.as<std::string>();
				}
			}
		}
    }
}

void YAMLParser::cargarArmas(const YAML::Node& nodeVect, GameConstants& info)
{
    for (unsigned i = 0; i < nodeVect.size(); ++i) {
        Arma arma;
        const YAML::Node& node = nodeVect[i];

        for(YAML::const_iterator it = node.begin(); it!=node.end(); ++it){
            std::string key(it->first.as<std::string>());
            if (key.compare("tipo") == 0){
                arma.nombre.assign(it->second.as<std::string>());
            } else if (key.compare("habilitada") == 0) {
                 arma.habilitada.assign(it->second.as<std::string>());
              } else if (key.compare("municiones") == 0) {
                  arma.municiones.assign(it->second.as<std::string>());
              }
          }
        asignar_a_info(arma, info);
    }
}

void YAMLParser::cargarMapa(const YAML::Node& nodeVect, std::vector<ElementInfo>& v, GameConstants& info)
{  
    ElementInfo elemento;
    for (unsigned i = 0; i < nodeVect.size(); ++i){
        const YAML::Node& node = nodeVect[i];
        elemento.reset();

        for(YAML::const_iterator it = node.begin(); it!=node.end(); ++it){
            std::string key(it->first.as<std::string>());
            if (key.compare("tipo") == 0){
                elemento.tipo = it->second.as<std::string>();
            } else if (key.compare("vida_gusanos") == 0) {
                info.worms_life = it->second.as<int>();
            } else if (key.compare("x") == 0) {
                elemento.x = it->second.as<float>();
            } else if (key.compare("y") == 0) {
                elemento.y = it->second.as<float>();
            } else if (key.compare("tamanio") == 0) {
                elemento.tam = it->second.as<std::string>();
            } else if (key.compare("angulo") == 0) {
                elemento.angulo = it->second.as<float>();
            }
        }
        v.push_back(elemento);
    }
}


void YAMLParser::asignar_a_info(Arma& arma, GameConstants& info)
{
    if (arma.nombre.compare(BANANA) == 0){
        info.banana_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(MORTERO) == 0){
        info.morter_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(BAZOOKA) == 0){
        info.bazooka_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(TELETRANSPORTACION) == 0){
        info.teleport_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(GRANADA_VERDE) == 0){
        info.green_granade_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(GRANADA_ROJA) == 0){
        info.red_granade_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(GRANADA_SANTA) == 0){
        info.saint_granade_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(ATAQUE_AEREO) == 0){
        info.air_attack_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(BATE) == 0){
        info.bat_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    } else if (arma.nombre.compare(DINAMITA) == 0) {
        info.dynamite_ammunition = this->toAmmunition(arma.habilitada, arma.municiones);
    }
}

int YAMLParser::toAmmunition(std::string& habilitada, std::string& municion){
	if (habilitada.compare("si") == 0){
		return (municion.compare(INFINITO) == 0)? -1 : std::stoi(municion);
	} else {
		return 0;
	}
}
