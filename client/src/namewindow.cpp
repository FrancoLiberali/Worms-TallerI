#include "namewindow.h"

#include "ui_namewindow.h"

#include <QString>
#include <QMessageBox>
#include <iostream>

#define MAX_LARGE 30

nameWindow::nameWindow(ProxyClient& proxy, std::string& name, QWidget *parent) :
    QDialog(parent), ui(new Ui::nameWindow), proxy(proxy), name(name)
{
    ui->setupUi(this);
    this->setWindowTitle("Solicitud de nombre");
}

nameWindow::~nameWindow()
{
    delete ui;
    delete connectW;
}

void nameWindow::on_btn_ok_clicked(){
    name = ui->nameLine->text().toStdString();
    if (name.length() == 0){
        QMessageBox::warning(this, "ERROR", "Debe ingresar algún nombre");
        return;
    }

    connectW = new connectWindow(proxy);
    close();
    connectW->show();
}
