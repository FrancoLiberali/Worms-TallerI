#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QCloseEvent>
#include "ProxyClient.h"
#include <string>

enum widget : int {
    HOME,
    NAME,
    CONNECT
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ProxyClient& proxy, std::string& name, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_playButton_clicked();
    void on_nameButtonBox_accepted();
    void on_nameButtonBox_rejected();
    void on_connectButtonBox_accepted();
    void on_connectButtonBox_rejected();
    // Atrapa el evento al querer cerrar la ventana.
    // Muestra una ventana para confirmar la accion.
    void closeEvent (QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    ProxyClient& proxy;
    std::string& name;
};

#endif // MAINWINDOW_H
