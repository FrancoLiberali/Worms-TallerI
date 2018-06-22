#include "vigachica.h"
#include <QPoint>
#include "conversor.h"
#include "../config.h"
#define POS_INICIAL QPointF(20,20)

VigaChica::VigaChica(int angulo) : Viga(angulo)
{
    // Setear las imagenes.
    QPixmap viga(_INSTALL_PATH_ "/recursos/vigac.png");
    setPixmap(viga);
    // Inicializar.
    setRotation((-1)*angulo);
    setPos(POS_INICIAL);
    // Flags.
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

 void VigaChica::escribir(YAML::Emitter& out) const
 {
     QPair<float, float> centro = this->conversor.a_metros(*this, this->angulo);
     out << YAML::BeginMap;
     out << YAML::Key << "tipo";
     out << YAML::Value << "viga";
     out << YAML::Key << "tamanio";
     out << YAML::Value << "chica";
     out << YAML::Key << "angulo";
     out << YAML::Value << this->conversor.a_radianes(this->angulo);
     out << YAML::Key << "x";
     out << YAML::Value << centro.first;
     out << YAML::Key << "y";
     out << YAML::Value << centro.second;
     out << YAML::EndMap;
 }

VigaChica::~VigaChica() {}
