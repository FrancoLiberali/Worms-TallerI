#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <string>
#include "ProxyClient.h"

namespace Ui {
class resultwindow;
}

class resultwindow : public QDialog
{
    Q_OBJECT

public:
    explicit resultwindow(ProxyClient& proxy, QWidget *parent = 0);
    ~resultwindow();
    void setResult(std::string& txtResult);

private slots:
    void on_btn_aceptar_clicked();

private:
    Ui::resultwindow *ui;
    ProxyClient& proxy;
};

#endif // RESULTWINDOW_H
