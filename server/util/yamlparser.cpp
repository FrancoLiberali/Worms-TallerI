#include "util/yamlparser.h"
#include "game_constants.h"

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

void YAMLParser::cargarConfig(unsigned int id, std::vector<elemento_t>& v, GameConstants& info)
{
    std::string nombre = std::to_string(id).append(".yaml");
    YAML::Node config = YAML::LoadFile(nombre);
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it){
        std::string key(it->first.as<std::string>());
        if (key.compare("armas") == 0){
            cargarArmas(it->second, info);
        }
        if (key.compare("objetos") == 0){
            cargarMapa(it->second, v);
        }
    }
}

void YAMLParser::cargarArmas(const YAML::Node& nodeVect, GameConstants& info)
{
    for (unsigned i = 0; i < nodeVect.size(); ++i) {
        arma_t arma;
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

void YAMLParser::cargarMapa(const YAML::Node& nodeVect, std::vector<elemento_t>& v)
{  
    elemento_t elemento;
    for (unsigned i = 0; i < nodeVect.size(); ++i){
        const YAML::Node& node = nodeVect[i];

        for(YAML::const_iterator it = node.begin(); it!=node.end(); ++it){
            std::string key(it->first.as<std::string>());
            if (key.compare("tipo") == 0){
                elemento.tipo = it->second.as<std::string>();
            } else if (key.compare("x") == 0) {
                elemento.x = it->second.as<float>();
            } else if (key.compare("y") == 0) {
                elemento.y = it->second.as<float>();
            } else if (key.compare("equipo") == 0) {
                elemento.equipo = it->second.as<int>();
            } else if (key.compare("tamanio") == 0) {
                elemento.tam = it->second.as<std::string>();
            } else if (key.compare("angulo") == 0) {
                elemento.angulo = it->second.as<float>();
            }
        }
        v.push_back(elemento);
    }
}


void asignar_a_info(arma_t& arma, GameConstants& info)
{
    if (arma.nombre.compare(BANANA)){
        info.bannana_enabled = decidir_habilitada(arma.habilitada);
        info.banana_ammunition = convertir_municion(arma.municion)
    } else if (arma.nombre.compare(MORTERO)){
        info.morter_enabled = decidir_habilitada(arma.habilitada);
        info.morter_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(BAZOOKA)){
        info.bazooka_enabled = decidir_habilitada(arma.habilitada);
        info.bazooka_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(TELETRANSPORTACION)){
        info.teleport_enabled = decidir_habilitada(arma.habilitada);
        info.teleport_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(GRANADA_VERDE)){
        info.green_granade_enabled = decidir_habilitada(arma.habilitada);
        info.green_granade_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(GRANADA_ROJA)){
        info.red_granade_enabled = decidir_habilitada(arma.habilitada);
        info.red_granade_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(GRANADA_SANTA)){
        info.holy_granade_enabled = decidir_habilitada(arma.habilitada);
        info.holy_granade_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(ATAQUE_AEREO)){
        info.air_attack_enabled = decidir_habilitada(arma.habilitada);
        info.air_attack_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(BATE)){
        info.bat_enabled = decidir_habilitada(arma.habilitada);
        info.bat_ammunition = convertir_municion(arma.municion);
    } else if (arma.nombre.compare(DINAMITA)) {
        info.dynamite_enabled = decidir_habilitada(arma.habilitada);
        info.dynamite_ammunition = convertir_municion(arma.municion);
    }
}

bool decidir_habilitada(std::stirng& habilitada)
{
    return habilitada.compare("si") ? true : false;
}

int convertir_municion(std::string& municion)
{
    return municion.compare(INFINITO)? -1 : std::stoi(municion);
}
