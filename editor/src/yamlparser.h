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
};

#endif // PARSER_H
