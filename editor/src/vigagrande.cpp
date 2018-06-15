#include "vigagrande.h"
#include <QGraphicsScene>
#include <iostream>
#define POS_INICIAL QPointF(20,20)

VigaGrande::VigaGrande(int angulo) : Viga(angulo)
{
    // Setear las imagenes.
    QPixmap viga("/usr/local/recursos/viga.png");
    setPixmap(viga);
    // Inicializar.
    setPos(POS_INICIAL);
    setRotation((-1)*angulo);
    // Flags.
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void VigaGrande::escribir(YAML::Emitter& out) const
{
    QPair<float, float> centro = this->conversor.a_metros(*this, this->angulo);
    out << YAML::BeginMap;
    out << YAML::Key << "tipo";
    out << YAML::Value << "viga";
    out << YAML::Key << "tamanio";
    out << YAML::Value << "grande";
    out << YAML::Key << "angulo";
    out << YAML::Value << this->conversor.a_radianes(this->angulo);
    out << YAML::Key << "x";
    out << YAML::Value << centro.first;
    out << YAML::Key << "y";
    out << YAML::Value << centro.second;
    out << YAML::EndMap;
}

VigaGrande::~VigaGrande() {}
