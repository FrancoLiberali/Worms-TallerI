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
    std::string name2("\nSucces");
    proxy.sendName(name2);
    done = true;
}

void mapWindow::on_btn_crear_clicked(){
    std::string nameRoom = ui->lineNameRoom->text().toStdString();
    int numPlayer = ui->cmb_jugadores->currentText().toInt();
    std::string nameMap = ui->cmb_maps->currentText().toStdString();
    
    proxy.sendCreateRoom(nameRoom, numPlayer, nameMap);
    close();
}

void mapWindow::addMap(std::string& map){
    std::cout << "add map " <<std::endl;
    ui->cmb_maps->addItem(map.c_str());
}
