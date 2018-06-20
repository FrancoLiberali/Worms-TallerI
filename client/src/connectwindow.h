#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H
#include "mapwindow.h"
#include <QDialog>
#include <string>
#include "common/socket.h"
#include "ProxyClient.h"
#include "common/socket_error.h"

namespace Ui {
class connectWindow;
}

class connectWindow : public QDialog {
    Q_OBJECT

private:
    Ui::connectWindow *ui;
    ProxyClient& proxy;
public:
    explicit connectWindow(ProxyClient& proxy, QWidget *parent = 0);
    ~connectWindow();

private slots:
    void on_pushButton_clicked();
};

#endif
