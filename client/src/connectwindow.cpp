#include "connectwindow.h"
#include "ui_connectwindow.h"
#include <QMessageBox>

#include <iostream>

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "7777"

connectWindow::connectWindow(ProxyClient& proxy, QWidget *parent) :
    QDialog(parent), ui(new Ui::connectWindow), proxy(proxy)
{
    ui->setupUi(this);
    // Valores por defecto.
    ui->ipLine->setText(DEFAULT_IP);
    ui->portLine->setText(DEFAULT_PORT);
    // Nombre de ventana.
    this->setWindowTitle("Loguearse");
}

connectWindow::~connectWindow(){
    delete ui;
}

void connectWindow::on_pushButton_clicked(){
    
    std::string host = ui->ipLine->text().toStdString();
    std::string port = ui->portLine->text().toStdString();

    Socket socket;
    try{
        proxy.connect(host, port);
	} catch(SocketError& e){
		//std::cout<<e.what()<<std::endl;
        QMessageBox::warning(this, "Error al conectar", e.what());
		return;
	}
    close();
}
