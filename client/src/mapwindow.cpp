#include "mapwindow.h"
#include "ui_mapwindow.h"
#include <QMessageBox>
#include <iostream>

#define INVALID_NAME_ROOM_MSJ "El nombre de la sala es invalido"
#define EMPTY_ROOMS_MSJ "No hay salas disponibles"

mapWindow::mapWindow(ProxyClient& proxy, QWidget *parent) :
    QDialog(parent),ui(new Ui::mapWindow), proxy(proxy), done(false)
{
    ui->setupUi(this);
}

mapWindow::~mapWindow()
{
    //proxy.close();
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
    close();
}


void mapWindow::on_btn_crear_clicked(){
    std::string nameRoom = ui->lineNameRoom->text().toStdString();
    if (verifyValid(nameRoom, INVALID_NAME_ROOM_MSJ)) return;

    int numPlayer = ui->cmb_jugadores->currentText().toInt();
    std::string nameMap = ui->cmb_maps->currentText().toStdString();
    
    proxy.sendCreateRoom(nameRoom, numPlayer, nameMap);
    close();
}

void mapWindow::addMap(std::string& map){
    ui->cmb_maps->addItem(map.c_str());
}

void mapWindow::addRoom(Room* room){
    std::cout << "add sala " <<std::endl;

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
