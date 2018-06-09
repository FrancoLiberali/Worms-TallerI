#include "ProxyClient.h"
#include <iostream>

 ProxyClient::ProxyClient(std::string socket):socket(socket){ 
 }
   
ProxyClient::~ProxyClient(){
    std::cout << "cerrar socket" << std::endl;
}

void  ProxyClient::sendInt(int num){
    std::cout<<num <<std::endl;
}

void ProxyClient::sendChar(char byte){
    std::cout<<(int)byte<<std::endl; 
}
int ProxyClient::receiveInt(){
    return 0;
}
char ProxyClient::receiveChar(){
    return 0;
}

void ProxyClient::close(){

}