#include "ProxyClient.h"
#include <arpa/inet.h>
#include "common/socket_error.h"
#include <iostream>
#include <cstring>

#define BYTE 1
#define MAX_NAME_LEN 20

#define ESCALA (140/6)

ProxyClient::ProxyClient(Socket socket): socket(std::move(socket)), open(true){
}
 
ProxyClient::~ProxyClient() noexcept{
    close();
}

void ProxyClient::addModel(Model* model){
    this->model = model;
}

void ProxyClient::connect(std::string& host, std::string& port){
    socket.connect_(host.c_str(), port.c_str());
}

void ProxyClient::close(){
    if (!open)
        return;
    this->socket.shutdown_();
    printf("Cerro\n");
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
    //printf("Posy: %i\n", pos_mm);
    return (-pos_mm*ESCALA/1000);
}

int ProxyClient::receivePosX(){
    int pos_mm = receiveInt();
    //printf("Posx: %i\n", pos_mm);
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


int ProxyClient::receiveWidht(){
    int w = receiveInt();
    return w*ESCALA/1000;
}
int ProxyClient::receiveHeight(){
    int h = receiveInt();
    return h*ESCALA/1000;
}


std::string ProxyClient::receiveName(){
    char buffer[MAX_NAME_LEN];
    memset(buffer, 0, MAX_NAME_LEN);
    int size = receiveInt();
    //std::cout << "SIZE NAME " << size <<std::endl;
    socket.receive_(buffer, size);
    return std::string((char*)buffer);
}

void ProxyClient::sendName(std::string& name){
    //std::cout<<"Send name "<< name<<std::endl;
    //sendChar(0);
    //sendInt(id);
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

void ProxyClient::sendCreateRoom(std::string& nameRoom,int  numPlayer,std::string nameMap){
    sendChar(13);
    sendInt(model->getIdPlayer());
    sendInt(numPlayer);
    sendName(nameMap);
    sendName(nameRoom);
    //std::cout<<" "<< model->getIdPlayer() << " "<< numPlayer << nameMap << nameRoom <<std::endl;
}

void ProxyClient::sendJoinRoom(int idRoom){
    sendChar(12);
    sendInt(model->getIdPlayer());
    sendInt(idRoom);
    std::cout<<"JOIN room "<<idRoom <<std::endl;
}

void ProxyClient::sendTeledirigido(int x, int y){
    sendChar(14);
    sendInt((x/ESCALA)*1000);
    sendInt((y/ESCALA)*1000);
    std::cout<<"enviar teledirigo "<<(x/ESCALA)*1000<<"-"<<(y/ESCALA)*1000<<std::endl;
}
