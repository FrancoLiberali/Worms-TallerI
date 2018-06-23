#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../config.h"

#include <QMessageBox>

#define ERROR_MSJ "Debe ingresar algún nombre"
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "7777"

MainWindow::MainWindow(ProxyClient& proxy, std::string& name, QWidget *parent) :
QMainWindow(parent),ui(new Ui::MainWindow), proxy(proxy), name(name)
{
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
    
    // Nombre de ventana.
    this->setWindowTitle("WORMS");

    // Setear imagen.
    ui->homeImgLabel->setPixmap(QPixmap(_INSTALL_PATH_ "/resource/images/a.png"));
    ui->homeImgLabel->show();

    // Default labels.
    ui->ipLine->setText(DEFAULT_IP);
    ui->portLine->setText(DEFAULT_PORT);
}

void MainWindow::on_playButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(NAME);
}

void MainWindow::on_nameButtonBox_accepted()
{
   name = ui->nameLine->text().toStdString();
   if (name.length() == 0){
       QMessageBox::warning(this, "ERROR", ERROR_MSJ);
       return;
   }
    ui->stackedWidget->setCurrentIndex(CONNECT);
}

void MainWindow::on_nameButtonBox_rejected()
{
    ui->stackedWidget->setCurrentIndex(HOME);
}

void MainWindow::on_connectButtonBox_accepted()
{
   std::string host(ui->ipLine->text().toStdString());
   std::string port(ui->portLine->text().toStdString());

    try{
        proxy.connect(host, port);
    } catch(SocketError& e){
        QMessageBox::warning(this, "Error al conectar", e.what());
        return;
    }
    close();
}

void MainWindow::on_connectButtonBox_rejected()
{
     ui->stackedWidget->setCurrentIndex(NAME);
}

// void MainWindow::closeEvent (QCloseEvent *event)
// {
//     QMessageBox::StandardButton resBtn = QMessageBox::question( this, "WORMS",
//                                                                 tr("Desea salir?\n"),
//                                                                 QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
//                                                                 QMessageBox::Yes);
//     if (resBtn != QMessageBox::Yes) {
//         event->ignore();
//     } else {
//         exit(EXIT_FAILURE);
//     }
// }

MainWindow::~MainWindow()
{
    delete ui;
}
