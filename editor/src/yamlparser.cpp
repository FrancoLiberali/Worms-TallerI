#include "yamlparser.h"
#include <QString>

YAMLParser::YAMLParser() {}

void YAMLParser::cargarConfig(Registro& registro)
{
    YAML::Node config = YAML::LoadFile("/home/bauticanavese/Demo/recursos/default_armo.yaml");
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it){
        std::string key(it->first.as<std::string>());
        if (key.compare("armas") == 0){
            cargarArmas(it->second, registro);
        }
        if (key.compare("objetos") == 0){
            //cargarMapa(it->second, registro);
        }
    }
}

void YAMLParser::cargarArmas(const YAML::Node& nodeVect, Registro& registro)
{
    for (unsigned i = 0; i < nodeVect.size(); ++i){
        Arma* arma = new Arma();
        std::string tipo;
        const YAML::Node& node = nodeVect[i];

        for(YAML::const_iterator it = node.begin(); it!=node.end(); ++it){
            std::string key(it->first.as<std::string>());
            if (key.compare("tipo") == 0){
                tipo.assign(it->second.as<std::string>());
                arma->set_tipo(tipo);
            } else if (key.compare("habilitada") == 0) {
                arma->set_habilitada();
            } else if (key.compare("municiones") == 0) {
                arma->set_municion(it->second.as<std::string>());
            }
        }
        registro.agregar_arma(tipo, arma);
    }
}
