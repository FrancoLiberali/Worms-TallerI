#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <string>
#include "game/game_constants.h"

// Estrutura que guarda la informacion de un arma del juego
struct Arma{
	std::string nombre;
	std::string habilitada;
	std::string municiones;
};

//Estrutura que guarda la informacion para la creacion de un elemento del mapa
struct ElementInfo{
	std::string tipo;
	std::string tam;
	float x;
	float y;
	float angulo;
	
	void reset(){
		this->tipo = "";
		this->tam = "";
		this->x = 0;
		this->y = 0;
		this->angulo = 0;
	}
};

class YAMLParser {
public:
    // Construye YAMLParser.
    YAMLParser();
    // Carga un mapa.
    // Recibe el nombre del mapa, un vector de elementos y las constantes del juego.
    // En "v" se almacena todos los objetos que componen el mapa.
    void cargarConfig(const std::string& name, std::vector<ElementInfo>& v,
     GameConstants& info);
     
    // Carga las armas.
    // Recibe un nodo con la informacion, y las constantes del juego
    // en donde se va a almacenar la informacion de las armas.
    void cargarArmas(const YAML::Node& nodeVect, GameConstants& info);
   
   	// Carga el mapa.
    // Recibe un nodo con la informacion, y un vector en donde se va
    // a almacenar la misma.
	void cargarMapa(const YAML::Node& nodeVect, std::vector<ElementInfo>& v, GameConstants& info);
	
	// Modifica las constantes segun el arma.
    void asignar_a_info(Arma& arma, GameConstants& info);
    
    // Decide si esta habilitada o no.
	// Convierte la municion a un entero.
	// Recibe municion como un string.
	// En caso de ser "infinitas" devuelve -1.
	int toAmmunition(std::string& habilitada, std::string& municion);

};
#endif // PARSER_H
