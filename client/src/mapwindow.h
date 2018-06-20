#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>
#include "ProxyClient.h"
#include "common/Thread.h"

namespace Ui {
class mapWindow;
}

class ProxyClient;

class mapWindow : public QDialog{
    Q_OBJECT

private:
    Ui::mapWindow *ui;
    ProxyClient& proxy;
    bool done;
public:
    explicit mapWindow(ProxyClient& proxy, QWidget *parent = 0);
    ~mapWindow();
    void addMap(std::string& map);
    void run();
private slots:

    void on_btn_unirse_clicked();

    void on_btn_crear_clicked();
};

#endif // MAPWINDOW_H
