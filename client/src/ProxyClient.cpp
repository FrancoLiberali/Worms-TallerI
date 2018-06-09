#include "ProxyClient.h"
#include <arpa/inet.h>
#include "common/socket_error.h"
#include <iostream>

ProxyClient::ProxyClient(Socket socket): sktClient(std::move(socket)){
 }
 
ProxyClient::ProxyClient(){}

ProxyClient::~ProxyClient() noexcept{
    std::cout << "cerrar socket" << std::endl;
}

void ProxyClient::close(){
    this->sktClient.shutdown_();
}

void  ProxyClient::sendInt(int num){
    std::cout<<num <<std::endl;
    int to_send = htonl(num);
    sktClient.send_((char*)&to_send, 4);
}

void ProxyClient::sendChar(char byte){
    std::cout<<(int)byte<<std::endl;
    sktClient.send_(&byte, 1);
}
int ProxyClient::receiveInt(){
    int num = 0;
    sktClient.receive_((char*)&num, 4);
    return ntohl(num);
}
char ProxyClient::receiveChar(){
    char received = 0;
    sktClient.receive_(&received, 1);
    return received;
}