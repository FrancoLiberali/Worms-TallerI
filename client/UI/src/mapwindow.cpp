#include "mapwindow.h"
#include "ui_mapwindow.h"

mapWindow::mapWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Elegir mapa");
    // Agrego los mapas disponibles.
    ui->mapsComboBox->addItem("Mapa 1");
    ui->mapsComboBox->addItem("Mapa 2");
    ui->mapsComboBox->addItem("Mapa 3");
    // Salas disponibles.
    ui->lobbyComboBox->addItem("Sala 1");
    ui->lobbyComboBox->addItem("Sala 2");
    ui->lobbyComboBox->addItem("Sala 3");
}

mapWindow::~mapWindow()
{
    delete ui;
}

void mapWindow::on_crearPartidaButton_clicked()
{
    // Aca crear partida (extraer nombre de mapa de mapsComboBox)
}

void mapWindow::on_unirseButton_clicked()
{
    // Aca unirse a partida.

    // Obtener el texto seleccinado: ui->comboBox->currentText()
}
