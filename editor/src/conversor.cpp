#include "conversor.h"

#define ESCALA (140/6)

Conversor::Conversor() {}

QPair<float,float> Conversor::a_metros(const QGraphicsPixmapItem &obj, float angulo) const
{
    float x_centro, y_centro;
    float alto = obj.pixmap().height();
    float ancho = obj.pixmap().width();
    angulo = a_radianes(angulo);
    float radio = ancho/2;
    x_centro = obj.pos().x() + alto/2 * qSin(angulo) + radio * qCos(angulo);
    y_centro = obj.pos().y() + alto/2 * qCos(angulo) - radio * qSin(angulo);
    x_centro = pixel_a_metros(x_centro);
    y_centro = pixel_a_metros(y_centro);
    return QPair<float,float>(x_centro, y_centro);
}


QPointF Conversor::a_pixeles(const QGraphicsPixmapItem &obj, float x_centro, float y_centro,  \
    float angulo) const
{
    float x, y;
    float alto = obj.pixmap().height();
    float ancho = obj.pixmap().width();
    float radio = ancho/2;
    x = metros_a_pixel(x_centro) - alto/2 * qSin(angulo) - radio * qCos(angulo);
    y = metros_a_pixel(y_centro) - alto/2 * qCos(angulo) + radio * qSin(angulo);
    return QPointF(x, y);
}

double Conversor::a_radianes(float angulo) const
{
    return qDegreesToRadians(angulo);
}

float Conversor::pixel_a_metros(float pixel) const 
{
    return pixel / ESCALA;
}

float Conversor::metros_a_pixel(float metro) const
{
    return  metro * ESCALA;
}

int Conversor::a_sexagesimal(float angulo) const
{
    return (angulo * 180) / (atan(1) * 4);
}
