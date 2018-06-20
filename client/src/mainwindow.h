#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "namewindow.h"
#include "ProxyClient.h"
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ProxyClient& proxy, std::string& name, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    nameWindow *nameW;
    ProxyClient& proxy;
    std::string& name;
};

#endif // MAINWINDOW_H
