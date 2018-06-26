#include "gusano.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../config.h"
#define POS_INICIAL QPointF(10,10)

Gusano::Gusano() : eliminado(false)
{
    // Seteando la imagen.
    setPixmap(QPixmap(_INSTALL_PATH_ "/recursos/gusano.png").scaled(32,\
        32, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    // Posicion inicial dentro del editor.
    setPos(POS_INICIAL);

    // Seteando los flags.
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Gusano::set_eliminado()
{
    eliminado = true;
}

bool Gusano::esta_eliminado()
{
    return eliminado;
}

void Gusano::set_pos(QPointF pos) {
    setPos(pos);
}

YAML::Emitter& operator << (YAML::Emitter& out, const Gusano &obj)
{
    QPair<float, float> centro = obj.conversor.a_metros(obj, 0);
    out << YAML::BeginMap;
    out << YAML::Key << "tipo";
    out << YAML::Value << "gusano";
    out << YAML::Key << "x";
    out << YAML::Value << centro.first;
    out << YAML::Key << "y";
    out << YAML::Value << centro.second;
    out << YAML::EndMap;
    return out;
}

Gusano::~Gusano() {}
