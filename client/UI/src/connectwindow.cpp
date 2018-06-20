#include "connectwindow.h"
#include "ui_connectwindow.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "7777"

connectWindow::connectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectWindow)
{
    ui->setupUi(this);
    // Valores por defecto.
    ui->ipLine->setText(DEFAULT_IP);
    ui->portLine->setText(DEFAULT_PORT);
    // Nombre de ventana.
    this->setWindowTitle("Loguearse");

    this->mapW = new mapWindow();
    connect(ui->buttonBox, SIGNAL(accepted()), this->mapW, SLOT(show()));

}

connectWindow::~connectWindow()
{
    delete ui;
    delete mapW;
}
