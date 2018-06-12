#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <string>
#include "game_constants.h"

typedef struct {
	std::string nombre;
	std::string habilitada;
	std::string municiones;
} arma_t;

typedef struct {
	// Hacer public.
	std::string nombre;
	std::string tam;
	float x;
	float y;
	float angulo = 0;
	int equipo;
} elemento_t;

class YAMLParser {
public:
    // Construye YAMLParser.
    YAMLParser();
    // Carga un mapa.
    // Recibe el id del mapa, un vector de elementos y las constantes del juego.
    // En "v" se almacena todos los objetos que componen el mapa.
    void cargarConfig(unsigned int id, std::vector<elemento_t>& v,
     GameConstants& info);
    // Carga las armas.
    // Recibe un nodo con la informacion, y un map en donde se va
    // a almacenar la misma.
    void cargarArmas(const YAML::Node& nodeVect, GameConstants& info);
    // Modifica las constantes segun el arma.
    void asignar_a_info(arma_t& arma, GameConstants& info);
    // Decide si esta habilitada o no.
	bool decidir_habilitada(std::string& habilitada);
	// Convierte la municion a un entero.
	// Recibe municion como un string.
	// En caso de ser "infinitas" devuelve -1.
	int convertir_municion(std::string& municion);
	// Carga el mapa.
    // Recibe un nodo con la informacion, y un map en donde se va
    // a almacenar la misma.
	void cargarMapa(const YAML::Node& nodeVect, std::vector<elemento_t>& v);

#endif // PARSER_H
