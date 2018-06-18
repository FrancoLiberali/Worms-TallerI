#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <string>
#include "game_constants.h"

struct Arma{
	std::string nombre;
	std::string habilitada;
	std::string municiones;
};

struct ElementInfo{
	std::string tipo;
	std::string tam;
	float x;
	float y;
	float angulo = 0;
	int equipo;
};

class YAMLParser {
public:
    // Construye YAMLParser.
    YAMLParser();
    // Carga un mapa.
    // Recibe el id del mapa, un vector de elementos y las constantes del juego.
    // En "v" se almacena todos los objetos que componen el mapa.
    void cargarConfig(std::string& name, std::vector<ElementInfo>& v,
     GameConstants& info);
    // Carga las armas.
    // Recibe un nodo con la informacion, y un map en donde se va
    // a almacenar la misma.
    void cargarArmas(const YAML::Node& nodeVect, GameConstants& info);
    // Modifica las constantes segun el arma.
    void asignar_a_info(Arma& arma, GameConstants& info);
    // Decide si esta habilitada o no.
	bool decidir_habilitada(std::string& habilitada);
	// Convierte la municion a un entero.
	// Recibe municion como un string.
	// En caso de ser "infinitas" devuelve -1.
	int convertir_municion(std::string& municion);
	// Carga el mapa.
    // Recibe un nodo con la informacion, y un map en donde se va
    // a almacenar la misma.
	void cargarMapa(const YAML::Node& nodeVect, std::vector<ElementInfo>& v);

};
#endif // PARSER_H
