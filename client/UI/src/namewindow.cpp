#include "namewindow.h"

#include "ui_namewindow.h"
#include <QString>
#include <QMessageBox>

#define MAX_LARGE 30

nameWindow::nameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nameWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Solicitud de nombre");

    this->connectW = new connectWindow();
    connect(ui->buttonBox, SIGNAL(accepted()), this->connectW, SLOT(show()));
}

void nameWindow::on_buttonBox_accepted()
{
    QString name = ui->nameLine->text();
    // mandar nombre al server.
}

nameWindow::~nameWindow()
{
    delete ui;
    delete connectW;
}
