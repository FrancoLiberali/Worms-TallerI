#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <sstream>
#include <string>
#include <vector>
#include <QString>
#include "arma.h"
#include "registro.h"

struct ElementInfo {
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

class YAMLParser
{
public:
    // Construye YAMLParser.
    YAMLParser();
    // Carga un mapa.
    void cargarConfig(Registro& registro);
    // Carga las armas.
    // Recibe un nodo con la informacion, y un map en donde se va
    // a almacenar la misma.
    void cargarArmas(const YAML::Node& nodeVect, Registro& registro);

    void cargarArchivo(const char *name, Registro& registro);

    void cargarMapa(const YAML::Node& nodeVect, Registro& registro);
};

#endif // PARSER_H
