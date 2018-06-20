#ifndef NAMEWINDOW_H
#define NAMEWINDOW_H
#include "connectwindow.h"
#include "ProxyClient.h"

#include <QDialog>
#include <string>

namespace Ui {
class nameWindow;
}

class nameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit nameWindow(ProxyClient& proxy,std::string& name, QWidget *parent = 0);
    ~nameWindow();

private slots:

    void on_btn_ok_clicked();

private:
    Ui::nameWindow *ui;
    connectWindow *connectW;
    ProxyClient& proxy;
    std::string& name;
};

#endif // NAMEWINDOW_H
