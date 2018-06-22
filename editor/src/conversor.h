#ifndef CONVERSOR_H
#define CONVERSOR_H
#include <QtCore>
#include <QGraphicsPixmapItem>
#include <QPoint>

class Conversor
{
public:
    // Construye conversor.
    Conversor();
    // Convierte a metros la posicion del centro de un objeto.
    // Recibe el objeto y el angulo a cual fue rotado.
    // Devuelve un par, donde se encuentra la posicion x e y del centro
    // dada en metros segun la escala.
    QPair<float,float> a_metros(const QGraphicsPixmapItem &obj, float angulo) const;
    // Convierte un angulo a radiantes.
    // Recibe el angulo.
    // Devuelve el angulo en radianes.
    double a_radianes(float angulo) const;
    // Convierte un angulo de radianes a sexagesimal.
    // Recibe el angulo en radianes.
    // Devuelve el angulo en sexagesimal.
    //float a_sexagesimal(float angulo) const;
    // Convierte a pixeles la posicion del centro de un objeto.
    // Recibe la posicion en metros y el angulo a cual fue rotado.
    // Devuelve un par, donde se encuentra la posicion x e y de la esquina
    // superior izquierda.
    //QPointF a_pixeles(QPair<float,float> pos) const;

    // Convierte un pixel a metros segun la escala;
    float pixel_a_metros(float pixel) const; 
};

#endif // CONVERSOR_H
