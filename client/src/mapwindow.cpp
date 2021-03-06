#include "mapwindow.h"
#include "ui_mapwindow.h"
#include <QMessageBox>
#include <iostream>

#define INVALID_NAME_ROOM_MSJ "El nombre de la sala es invalido"
#define EMPTY_ROOMS_MSJ "No hay salas disponibles"
#define INVALID_MAP_MSJ "Debe elegir un mapa"

mapWindow::mapWindow(ProxyClient& proxy, QWidget *parent) :
    QDialog(parent),ui(new Ui::mapWindow), proxy(proxy), done(false)
{
    ui->setupUi(this);

    // Nombre de ventana.
    this->setWindowTitle("Lobby");
}

mapWindow::~mapWindow()
{
    delete ui;
}

void mapWindow::on_btn_unirse_clicked(){
    int id = 0;
    std::string name = ui->cmb_salas->currentText().toStdString();
    if (verifyValid(name, EMPTY_ROOMS_MSJ)) return;
    
    for (auto& it: this->rooms){
        if ( it.second->isName(name))
            id = it.first;
    }

    proxy.sendJoinRoom(id);
    accept();
}


void mapWindow::on_btn_crear_clicked(){
    std::string nameRoom = ui->lineNameRoom->text().toStdString();
    if (verifyValid(nameRoom, INVALID_NAME_ROOM_MSJ)) return;

    int numPlayer = ui->cmb_jugadores->currentText().toInt();
    std::string nameMap = ui->cmb_maps->currentText().toStdString();
    if (verifyValid(nameMap, INVALID_MAP_MSJ)) return;
    
    proxy.sendCreateRoom(nameRoom, numPlayer, nameMap);
    //limpio toda la información
    accept();
}

void mapWindow::addMap(std::string& map){
    ui->cmb_maps->addItem(map.c_str());
}

void mapWindow::addRoom(Room* room){
    this->rooms.emplace(room->getId(), room);
    ui->cmb_salas->addItem(room->getName().c_str());
}

bool mapWindow::verifyValid(const std::string& str, const char* errorMsj) {
    if (str.empty()) {
        QMessageBox::warning(this, "ERROR", errorMsj);
        return true;
    }
    return false;  
}
