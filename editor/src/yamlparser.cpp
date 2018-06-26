#include "yamlparser.h"
#include <QString>
#include "../config.h"
#include "gusano.h"
#include "vigagrande.h"
#include "vigachica.h"
#include "conversor.h"

YAMLParser::YAMLParser() {}


void YAMLParser::cargarArchivo(const char* name, Registro& registro)
{
    YAML::Node config = YAML::LoadFile(name);
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it){
        std::string key(it->first.as<std::string>());
        if (key.compare("armas") == 0){
            cargarArmas(it->second, registro);
        }
        if (key.compare("objetos") == 0){
            cargarMapa(it->second, registro);
        }
        if (key.compare("metadata") == 0){
            for(YAML::const_iterator it2 = it->second.begin(); it2!=it->second.end(); ++it2){
                std::string key2(it2->first.as<std::string>());
                if (key2.compare("fondo") == 0){
                    // std::string fondo(it->second.as<std::string>());
                    // registro.set_fondo(QString::fromUtf8(fondo.c_str()));
                }
            }
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


void YAMLParser::cargarMapa(const YAML::Node& nodeVect, Registro& registro)
{  
    Conversor conversor;
    ElementInfo elemento;
    for (unsigned i = 0; i < nodeVect.size(); ++i){
        const YAML::Node& node = nodeVect[i];
        elemento.reset();

        for(YAML::const_iterator it = node.begin(); it!=node.end(); ++it){
            std::string key(it->first.as<std::string>());
            if (key.compare("tipo") == 0){
                elemento.tipo = it->second.as<std::string>();
            } else if (key.compare("vida_gusanos") == 0) {
               registro.set_vida_gusanos(it->second.as<int>());
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

        if (elemento.tipo.compare("gusano") == 0) {
            Gusano *gusano = new Gusano();
            QPointF pos = conversor.a_pixeles(*gusano, elemento.x, elemento.y, 
                elemento.angulo);
            gusano->set_pos(pos);
            registro.agregar_gusano(gusano);
        } else if (elemento.tipo.compare("viga") == 0) {
            int angulo = conversor.a_sexagesimal(elemento.angulo);
            if (elemento.tam.compare("chica") == 0) {
                Viga *viga = new VigaChica(angulo);
                QPointF pos = conversor.a_pixeles(*viga, elemento.x, elemento.y, 
                    elemento.angulo);
                viga->set_pos(pos);
                registro.agregar_viga(viga);
            } else if (elemento.tam.compare("grande") == 0) {
                Viga *viga = new VigaGrande(angulo);
                QPointF pos = conversor.a_pixeles(*viga, elemento.x, elemento.y, 
                    elemento.angulo);
                viga->set_pos(pos);
                registro.agregar_viga(viga);
            }
        }
    }
}
