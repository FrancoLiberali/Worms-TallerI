#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "namewindow.h"
#include "../config.h"


MainWindow::MainWindow(ProxyClient& proxy, std::string& name, QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow), proxy(proxy), name(name)
{
    ui->setupUi(this);
    // Setear color.
    setStyleSheet("background-color: grey;");
    // Nombre ventana.
    this->setWindowTitle("Worms");

    // Setear imagen inicio.
    ui->label->setPixmap(QPixmap(_INSTALL_PATH_ "/resource/images/a.png"));
    ui->label->show();

    this->nameW = new nameWindow(proxy, name);

    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->playButton, SIGNAL(clicked()), this->nameW, SLOT(show()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
