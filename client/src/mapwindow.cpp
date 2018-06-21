#include "mapwindow.h"
#include "ui_mapwindow.h"

#include <iostream>

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
    for (auto& it: this->rooms){
        if ( it.second->isName(name))
            id = it.first;
    }

    proxy.sendJoinRoom(id);
    close();
}


void mapWindow::on_btn_crear_clicked(){
    std::string nameRoom = ui->lineNameRoom->text().toStdString();
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
