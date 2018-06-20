#include "mainwindow.h"
#include "mapwindow.h"

#include <QApplication>

#include "common/socket.h"
#include "ProxyClient.h"
#include "GameClient.h"

#include <iostream>
#include <string>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    Socket socket;
    bool is_connected = false;
    std::string name = "";
    ProxyClient proxy(std::move(socket));
    
    MainWindow w(proxy, name);
    w.show();
    a.exec();
    if (name.length() <= 0)
        return 0;
    GameClient game(proxy, name);
    game.run();
    return 0;
}
