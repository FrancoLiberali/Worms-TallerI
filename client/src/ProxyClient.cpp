#include "ProxyClient.h"
#include <arpa/inet.h>
#include "common/socket_error.h"
#include <iostream>
#define BYTE 1

ProxyClient::ProxyClient(Socket socket): socket(std::move(socket)){
}
 
ProxyClient::~ProxyClient() noexcept{
    std::cout << "cerrar socket" << std::endl;
}

void ProxyClient::close(){
    this->socket.shutdown_();
}

void  ProxyClient::sendInt(int num){
    int to_send = htonl(num);
    socket.send_((char*)&to_send, 4);
}

void ProxyClient::sendChar(char byte){
    socket.send_(&byte, BYTE);
}
int ProxyClient::receiveInt(){
    int num = 0;
    socket.receive_((char*)&num, 4);
    return ntohl(num);
}
char ProxyClient::receiveChar(){
    char received = 0;
    socket.receive_(&received, 1);
    return received;
}

std::string ProxyClient::receiveString(){
    int size = this->receiveInt();
    char* buff = new char[size];
    socket.receive_(buff, size);
    std::string msg(buff);
    delete[] buff;
    return msg;
}

void ProxyClient::sendName(std::string& name){
    std::cout<<"Send name"<< name<<std::endl;
    char cmd = 0;
    socket.send_(&cmd, BYTE);
    sendInt(name.length());
    socket.send_(name.data(), name.length());
}

void ProxyClient::sendMapAndPlayers(int idMap, int num){
    std::cout<<"Envio mapa "<<idMap << " jugadores "<<num<<std::endl;
    sendChar(1);
    sendInt(idMap);
    sendInt(num);
}

void ProxyClient::sendMoveWorm(int idPlayer, int dir){
    std::cout<<"move "<<idPlayer << " " <<dir<<std::endl;
    sendChar(2);
    sendInt(idPlayer);
    sendInt(dir);
}

void ProxyClient::sendJump(int dir, int idPlayer){
    char cmd = (dir == 1)? 2 : 3;
    std::cout<<"salto "<<(int)cmd << " " <<idPlayer<<std::endl;
    sendChar(cmd);
    sendInt(idPlayer);
}

void ProxyClient::sendWeaponSelect(int idPlayer, int idWeapon){
    std::cout<<"wepon "<< idPlayer <<" "<< idWeapon <<std::endl;
    sendChar(4);
    sendInt(idPlayer);
    sendInt(idWeapon);
}
