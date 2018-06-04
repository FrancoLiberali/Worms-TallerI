#include "ProxyClient.h"
#include <iostream>

 ProxyClient::ProxyClient(std::string socket):socket(socket){ 
 }
   
ProxyClient::~ProxyClient(){}

void  ProxyClient::sendInt(int num){
    std::cout<<num; 
}
void ProxyClient::sendByte(char byte){
    std::cout<<byte; 
}
int ProxyClient::receiveInt(){
    return 0;
}
char ProxyClient::receiveByte(){
    return 0;
}