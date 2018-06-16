#include "ProxyClient.h"
#include <arpa/inet.h>
#include "common/socket_error.h"
#include <iostream>
#include <cstring>

#define BYTE 1
#define MAX_NAME_LEN 20

#define ESCALA (140/6)
#define MILES

ProxyClient::ProxyClient(Socket socket): socket(std::move(socket)), open(true){
}
 
ProxyClient::~ProxyClient() noexcept{
}

void ProxyClient::close(){
    if (!open)
        return;
    this->socket.shutdown_();
    open = false;
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

int ProxyClient::receivePosY(){
    int pos_mm = receiveInt();
    return (-pos_mm*ESCALA/1000);
}

int ProxyClient::receivePosX(){
    int pos_mm = receiveInt();
    return (pos_mm*ESCALA/1000);
}

int ProxyClient::receiveAngle(){
    int angle = receiveInt();
    return (-angle);
}

char ProxyClient::receiveChar(){
    char received = 0;
    socket.receive_(&received, 1);
    return received;
}

std::string ProxyClient::receiveName(){
    char buffer[MAX_NAME_LEN];
    memset(buffer, 0, MAX_NAME_LEN);
    int size = receiveInt();
    //std::cout << "SIZE NAME " << size <<std::endl;
    socket.receive_(buffer, size);
    return std::string((char*)buffer);
}

void ProxyClient::sendName(int id, std::string& name){
    //std::cout<<"Send name "<< name<<std::endl;
    sendChar(0);
    sendInt(id);
    sendInt(name.length());
    socket.send_(name.data(), name.length());
}

void ProxyClient::sendMapAndPlayers(int idMap, int num){
    //std::cout<<"Envio mapa "<<idMap << " jugadores "<<num<<std::endl;
    sendChar(1);
    sendInt(idMap);
    sendInt(num);
}

void ProxyClient::sendMoveWorm(int idPlayer, int dir){
    //std::cout<<"move "<<idPlayer << " " <<dir<<std::endl;
    sendChar(2);
    sendInt(idPlayer);
    sendInt(dir);
}

void ProxyClient::sendJump(int idPlayer){
    //std::cout<<"jump "<<std::endl;

    sendChar(3);
    sendInt(idPlayer);
}
void ProxyClient::sendBackJump(int idPlayer){
    //std::cout<<"back jump "<<std::endl;

    sendChar(4);
    sendInt(idPlayer);
}

void ProxyClient::sendWeaponSelect(int idPlayer, int idWeapon){
    //std::cout<<"wepon "<< idPlayer <<" "<< idWeapon <<std::endl;
    sendChar(5);
    sendInt(idPlayer);
    sendInt(idWeapon);
}

void ProxyClient::sendChangeAim(int idPlayer, int delta){
    //std::cout<<"change aim "<< idPlayer <<" "<< delta <<std::endl;
    sendChar(6);
    sendInt(idPlayer);
    sendInt(delta);
}

void ProxyClient::sendChargePower(int idPlayer){
    //std::cout<<"Power Charge 8 "<< idPlayer <<std::endl;
    sendChar(8);
    sendInt(idPlayer);
}

void ProxyClient::sendWormShoot(int idPlayer){
    //std::cout<<"Shoot 9 "<< idPlayer <<std::endl;
    sendChar(9);
    sendInt(idPlayer);
}

void ProxyClient::sendCountDown(int idPlayer, int time){
    //std::cout<<"cuenta regresiva "<< idPlayer << " "<< time << std::endl;
    sendChar(7);
    sendInt(idPlayer);
    sendInt(time);
}