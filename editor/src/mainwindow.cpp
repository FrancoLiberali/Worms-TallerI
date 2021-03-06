#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vigagrande.h"
#include "vigachica.h"
#include "gusano.h"
#include "validadordemapa.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <QMessageBox>
#include <QFileInfo>
#include "../config.h"

#define MIN_ANGULO 0
#define MAX_ANGULO 360
#define ANCHO_MAPA 1800
#define ALTO_MAPA 1024

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    guardado(false)
{
    ui->setupUi(this);

    registro.set_tam_mapa(ANCHO_MAPA, ALTO_MAPA);
    
    // Crear y configurar la escena.
    scene = new QGraphicsScene(this);
    scene->setSceneRect(ui->graphicsView->x(), ui->graphicsView->y(), ANCHO_MAPA, ALTO_MAPA);
    // Asigno escena.
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    // Imagen de fondo default.
    ui->graphicsView->setBackgroundBrush(QBrush(
        QPixmap(_INSTALL_PATH_ "/recursos/fondos/sky3.png").scaled(ANCHO_MAPA, ALTO_MAPA)));
    this->setWindowTitle("Editor");

    // Cargar configuracion default de armas.
    armas = new ConfigArmas(this->registro, this);
    armas->setWindowTitle("Configurar armas");

    // Cargar configuracion default de gusanos.
    gusanos = new ConfigGusanos(this->registro, this);
    gusanos->setWindowTitle("Configurar gusanos");

    // Configuracion de layouts y spinbox.
    ui->gusano_leyout->setVisible(false);
    ui->viga_layout->setVisible(false);
    ui->verticalLayout->setAlignment(Qt::AlignTop);
    ui->spinBox_2->setRange(MIN_ANGULO, MAX_ANGULO);
}

void MainWindow::on_pushButton_clicked()
{
    ui->viga_layout->setVisible(!ui->viga_layout->isVisible());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->gusano_leyout->setVisible(!ui->gusano_leyout->isVisible());
}

void MainWindow::on_pushButton_3_clicked()
{
    Gusano *gusano = new Gusano();
    scene->addItem(gusano);
    registro.agregar_gusano(gusano);
    ui->graphicsView->centerOn(gusano);
}

void MainWindow::on_pushButton_4_clicked()
{
    int angulo = ui->spinBox_2->value();
    VigaGrande *viga = new VigaGrande(angulo);
    scene->addItem(viga);
    registro.agregar_viga(viga);
    ui->graphicsView->centerOn(viga);
}


void MainWindow::on_pushButton_5_clicked()
{
    int angulo = ui->spinBox_2->value();
    VigaChica *viga = new VigaChica(angulo);
    scene->addItem(viga);
    registro.agregar_viga(viga);
    ui->graphicsView->centerOn(viga);
}

void MainWindow::on_actionFondo_de_Pantalla_triggered()
{
    QString nombre_archivo = QFileDialog::getOpenFileName(
                this, 
                tr("Abrir Imagen"),
                _INSTALL_PATH_ "/recursos/fondos",
                tr("Images (*.png *.jpg)"));
    if (nombre_archivo.isEmpty()) return;
    
    ui->graphicsView->setBackgroundBrush(QBrush(QPixmap(nombre_archivo)));
    nombre_archivo = QFileInfo(nombre_archivo).fileName();
    registro.set_fondo(nombre_archivo);
}


void MainWindow::on_actionGusanos_triggered()
{
    gusanos->exec();
}

void MainWindow::on_actionArmas_triggered()
{
    armas->exec();
}


void MainWindow::on_actionSalir_triggered()
{   
    if(guardado) {
        this->close();
        return;
    }

    QMessageBox msgBox(this);
    msgBox.setText("El mapa fue modificado.");
    msgBox.setInformativeText("Desea guardal los cambios?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    
    switch (ret) {
        case QMessageBox::Save:
            on_actionsave_as_triggered();
            break;
        case QMessageBox::Discard:
            this->close();
            break;
        case QMessageBox::Cancel:
            msgBox.close();
            break;
         default:
            break;
    }
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
            registro.actualizar_gusano();
        }
        delete item;
    }
}

void MainWindow::on_actionsave_as_triggered()
{
    // Verifica el mapa.
    ValidadorDeMapa verifica;
    if(!verifica(registro)) {
        QMessageBox::warning(this, tr("ERROR"),
                               tr("El mapa que intenta guardar no es valido.\n"
                                  "Intente agregando mas gusanos, vigas o hablitando armas."));
        return;
    }

    // Solicita la ruta para guardar el mapa.
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Guardar Mapa"), 
            _INSTALL_PATH_ "/maps",
            tr("Address Book (*.yaml);;All Files (*)"));

    if (fileName.isEmpty()) return;

    // Crea el archivo yaml.
    YAML::Emitter out;
    out << registro;

    std::ofstream file(fileName.toStdString());
    file << out.c_str() << std::endl;
    file.close();

    this->guardado = true;

    QMessageBox msgBox(this);
    msgBox.setText("El mapa fue guardado correctamente.");
    msgBox.exec();
}



void MainWindow::on_actionOpen_triggered()
{   
    QMessageBox msgBox(this);
    msgBox.setText("Al abrir otro mapa perderas tus cambios.");
    msgBox.setInformativeText("Desea guardar el mapa actual?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
     
    if (!guardado) {
        int ret = msgBox.exec();
        
        switch (ret) {
            case QMessageBox::Save:
                on_actionsave_as_triggered();
                break;
            case QMessageBox::Discard:
                msgBox.close();
                break;
            case QMessageBox::Cancel:
                msgBox.close();
                return;
            }
    }

    // Archivo a abrir.
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Abrir Mapa"), 
            _INSTALL_PATH_ "/maps",
            tr("Address Book (*.yaml);;All Files (*)"));

    if (fileName.isEmpty()) return;

    // Eliminamos todos los objetos del mapa.
    borrarTodo();
    
    // Leemos el archivo.
    YAMLParser parser;
    parser.cargarArchivo(fileName.toStdString().c_str(), this->registro);

    // Agregamos los nuevos items del mapa.
    std::vector<QGraphicsPixmapItem*> v;
    registro.get_items(v);
    foreach (auto item, v) {
        scene->addItem(item);
    }
}


void MainWindow::borrarTodo() 
{
    foreach(QGraphicsItem* item, scene->items()) {
        scene->removeItem(item);
        delete item;
    }
    registro.clear();
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
