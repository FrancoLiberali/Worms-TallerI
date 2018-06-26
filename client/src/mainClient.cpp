#include "mainwindow.h"
#include <QApplication>

#include "common/socket.h"
#include "ProxyClient.h"
#include "GameClient.h"

#include <iostream>
#include <string>


int main(int argc, char *argv[]){
    QApplication worms(argc, argv);
    //Loguin inicial
    Socket socket;
    std::string name = "";
    ProxyClient proxy(std::move(socket));
    
    MainWindow wormsMenu(proxy, name);
    wormsMenu.show();
    worms.exec();
    try {
        proxy.sendName(name);
    } catch (SocketError& e){
        return 0;
    }
    
    //Inicio del juego
    GameClient game(proxy, name);
    game.run();
    return 0;
}
