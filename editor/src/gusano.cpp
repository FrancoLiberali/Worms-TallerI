#include "gusano.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define POS_INICIAL QPointF(10,10)

Gusano::Gusano(int equipo) : equipo(equipo), eliminado(false)
{
    // Seteando la imagen.
    set_pixmap(equipo);

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

int Gusano::get_equipo()
{
    return equipo;
}

YAML::Emitter& operator << (YAML::Emitter& out, const Gusano &obj)
{
    QPair<float, float> centro = obj.conversor.a_metros(obj, 0);
    out << YAML::BeginMap;
    out << YAML::Key << "tipo";
    out << YAML::Value << "gusano";
    out << YAML::Key << "equipo";
    out << YAML::Value << obj.equipo;
    out << YAML::Key << "x";
    out << YAML::Value << centro.first;
    out << YAML::Key << "y";
    out << YAML::Value << centro.second;
    out << YAML::EndMap;
    return out;
}

void Gusano::set_pixmap(int id)
{
    switch(id) {
        case EQUIPO_1:
            setPixmap(QPixmap(":/img/recursos/gusano1.png").scaled(32,\
             32, Qt::IgnoreAspectRatio, Qt::FastTransformation));
            break;
        case EQUIPO_2:
            setPixmap(QPixmap(":/img/recursos/gusano2.png").scaled(32,\
             32, Qt::IgnoreAspectRatio, Qt::FastTransformation));
            break;
        case EQUIPO_3:
            setPixmap(QPixmap(":/img/recursos/gusano3.png").scaled(32,\
             32, Qt::IgnoreAspectRatio, Qt::FastTransformation));
            break;
        case EQUIPO_4:
            setPixmap(QPixmap(":/img/recursos/gusano4.png").scaled(32,\
             32, Qt::IgnoreAspectRatio, Qt::FastTransformation));
            break;
    }
}

Gusano::~Gusano() {}
