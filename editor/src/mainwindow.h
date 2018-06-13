#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include "registro.h"
#include "configarmas.h"
#include "configgusanos.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // Boton seleccion de viga.
    // Habilita el layout configurable para la viga.
    void on_pushButton_clicked();
    // Boton seleccion de gusano.
    // Habilita el layout configurable para el gusano.
    void on_pushButton_2_clicked();
    // Boton que crea un gusano.
    void on_pushButton_3_clicked();
    // Boton que crea una viga.
    void on_pushButton_4_clicked();
    // Permite seleccionar un fondo de pantalla para el mapa.
    void on_actionFondo_de_Pantalla_triggered();
    // Ejecuta la ventana de configArmas.
    // Muestra las armas disponibles y da opcion a editar sus
    // especificaciones.
    void on_actionArmas_triggered();
    // Ejecuta la ventana de configGusanos.
    void on_actionGusanos_triggered();

    void on_pushButton_6_clicked();
    // Guardar mapa sobre un escritorio especifico.
    void on_actionsave_as_triggered();

    void on_pushButton_5_clicked();

    void on_actionSalir_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    // Ventana de configuracion de armas.
    ConfigArmas *armas;
    // Ventana de configuracion de gusanos.
    ConfigGusanos *gusanos;
    // Registro de cambios en el mapa.
    Registro registro;
    
    bool guardado;
};

#endif // MAINWINDOW_H
