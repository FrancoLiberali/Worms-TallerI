#include "ProxyClient.h"
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

#define BYTE 1
#define MAX_NAME_LEN 20
#define ESCALA (140/6)

enum MSG_PROTOCOL{
    MAP_AND_PLAYERS = 1,
    MOVE_WORM,
    DIRECT_JUMP,
    BACK_JUMP,
    WEAPON_SELECT,
    CHANGE_AIM,
    COUNTDOWN,
    CHARGE_POWER,
    WORM_SHOOT,
    LEAVE_ROOM = 11,
    JOIN_ROOM,
    CREATE_ROOM,
    TELEDIRIGIDO,
};

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
    socket.receive_(buffer, size);
    return std::string((char*)buffer);
}

void ProxyClient::sendName(std::string& name){
    sendInt(name.length());
    socket.send_(name.data(), name.length());
}

void ProxyClient::sendMapAndPlayers(int idMap, int num){
    sendChar(MAP_AND_PLAYERS);
    sendInt(idMap);
    sendInt(num);
}

void ProxyClient::sendMoveWorm(int idPlayer, int dir){
    sendChar(MOVE_WORM);
    sendInt(idPlayer);
    sendInt(dir);
}

void ProxyClient::sendJump(int idPlayer){
    sendChar(DIRECT_JUMP);
    sendInt(idPlayer);
}
void ProxyClient::sendBackJump(int idPlayer){
    sendChar(BACK_JUMP);
    sendInt(idPlayer);
}

void ProxyClient::sendWeaponSelect(int idPlayer, int idWeapon){
    sendChar(WEAPON_SELECT);
    sendInt(idPlayer);
    sendInt(idWeapon);
}

void ProxyClient::sendChangeAim(int idPlayer, int delta){
    sendChar(CHANGE_AIM);
    sendInt(idPlayer);
    sendInt(delta);
}

void ProxyClient::sendCountDown(int idPlayer, int time){
    sendChar(COUNTDOWN);
    sendInt(idPlayer);
    sendInt(time);
}

void ProxyClient::sendChargePower(int idPlayer){
    sendChar(CHARGE_POWER);
    sendInt(idPlayer);
}

void ProxyClient::sendWormShoot(int idPlayer){
    sendChar(WORM_SHOOT);
    sendInt(idPlayer);
}

void ProxyClient::sendLeaveRoom(){
    sendChar(LEAVE_ROOM);
    sendInt(model->getIdPlayer());
    model->keepPlaying();
}

void ProxyClient::sendJoinRoom(int idRoom){
    sendChar(JOIN_ROOM);
    sendInt(model->getIdPlayer());
    sendInt(idRoom);
}

void ProxyClient::sendCreateRoom(std::string& nameRoom,int  numPlayer,std::string nameMap){
    sendChar(CREATE_ROOM);
    sendInt(model->getIdPlayer());
    sendInt(numPlayer);
    sendName(nameMap);
    sendName(nameRoom);
}



void ProxyClient::sendTeledirigido(int idPlayer, int x, int y){
    sendChar(TELEDIRIGIDO);
    sendInt(idPlayer);
    sendInt((x/ESCALA)*1000);
    sendInt((y/ESCALA)*1000);
}

