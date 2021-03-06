#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>
#include "ProxyClient.h"
#include "Room.h"

#include <map>

namespace Ui {
class mapWindow;
}

class ProxyClient;

class mapWindow : public QDialog{
    Q_OBJECT

private:
    bool verifyValid(const std::string& str, const char* errorMsj);
    Ui::mapWindow *ui;
    ProxyClient& proxy;
    bool done;
    std::map<int, Room*> rooms;
public:
    explicit mapWindow(ProxyClient& proxy, QWidget *parent = 0);
    ~mapWindow();
    void addMap(std::string& map);
    void addRoom(Room* room);
    void run();
private slots:

    void on_btn_unirse_clicked();

    void on_btn_crear_clicked();
};

#endif // MAPWINDOW_H
