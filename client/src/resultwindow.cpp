#include "resultwindow.h"
#include "ui_resultwindow.h"

resultwindow::resultwindow(ProxyClient& proxy, QWidget *parent) :
    QDialog(parent), proxy(proxy),
    ui(new Ui::resultwindow)
{
    ui->setupUi(this);

    // Setear imagen.
    ui->label->setPixmap(QPixmap(_INSTALL_PATH_ "/resource/images/wgusano.png"));
    ui->label->show();
}

resultwindow::~resultwindow()
{
    delete ui;
}

void resultwindow::on_btn_aceptar_clicked()
{
  ui->lbl_result->setText("JAJAJ");
  this->proxy.sendLeaveRoom();
  accept();
}

void resultwindow::setResult(std::string& txtResult){
    ui->lbl_result->setText(txtResult.c_str());
}