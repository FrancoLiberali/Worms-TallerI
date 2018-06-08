#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vigagrande.h"
#include "vigachica.h"
#include "gusano.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFileDialog>
#include <fstream>
#include <iostream>

#define MIN_JUGADORES 1
#define MAX_JUGADORES 4
#define MIN_ANGULO 0
#define MAX_ANGULO 360

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    guardado(false)
{
    ui->setupUi(this);

    // Crear y configurar la escena.
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    // Cargar configuracion default de armas.
    armas = new ConfigArmas(this->registro, this);

    // Cargar configuracion default de gusanos.
    gusanos = new ConfigGusanos(this->registro, this);

    // Configuracion de layouts.
    ui->gusano_leyout->setVisible(false);
    ui->viga_layout->setVisible(false);
    ui->spinBox->setRange(MIN_JUGADORES, MAX_JUGADORES);
    ui->spinBox_2->setRange(MIN_ANGULO, MAX_ANGULO);
}

void MainWindow::on_pushButton_clicked()
{
    ui->gusano_leyout->setVisible(false);
    ui->viga_layout->setVisible(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->viga_layout->setVisible(false);
    ui->gusano_leyout->setVisible(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    int equipo = ui->spinBox->value();
    Gusano *gusano = new Gusano(equipo);
    scene->addItem(gusano);
    registro.agregar_gusano(equipo, gusano);
}

void MainWindow::on_pushButton_4_clicked()
{
    int angulo = ui->spinBox_2->value();
    VigaGrande *viga = new VigaGrande(angulo);
    scene->addItem(viga);
    registro.agregar_viga(viga);
}


void MainWindow::on_pushButton_5_clicked()
{
    int angulo = ui->spinBox_2->value();
    VigaChica *viga = new VigaChica(angulo);
    scene->addItem(viga);
    registro.agregar_viga(viga);
}

void MainWindow::on_actionFondo_de_Pantalla_triggered()
{
    QString nombre_archivo = QFileDialog::getOpenFileName(
                this,
                tr("Abrir Imagen de fondo"),
                "img (*.jpg)"
                );
    ui->graphicsView->setBackgroundBrush(QBrush(QPixmap(nombre_archivo)));
    // guardar file_name
}


void MainWindow::on_actionGusanos_triggered()
{
    gusanos->exec();
}

void MainWindow::on_actionArmas_triggered()
{
    armas->exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    foreach(QGraphicsItem* item, scene->selectedItems()) {
        scene->removeItem(item);
        if (item->type() == Viga::Type) {
            Viga* viga = dynamic_cast<Viga*>(item);
            viga->set_eliminado();
            registro.actualizar_vigas();
        } else if (item->type() == Gusano::Type) {
            Gusano* gusano = dynamic_cast<Gusano*>(item);
            gusano->set_eliminado();
            registro.actualizar_gusano(gusano->get_equipo());
        }
        delete item;
    }
}

void MainWindow::on_actionsave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Guardar Mapa"), "",
            tr("Address Book (*.yaml);;All Files (*)"));

    YAML::Emitter out;
    out << registro;

    std::ofstream file(fileName.toStdString());
    file << out.c_str() << std::endl;
    file.close();

    this->guardado = true;
}

MainWindow::~MainWindow()
{
    foreach (QGraphicsItem *item, scene->items()) {
        delete item;
    }
    delete ui;
    delete armas;
    delete gusanos;
    delete scene;
}
