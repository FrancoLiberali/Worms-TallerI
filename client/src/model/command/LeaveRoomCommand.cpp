#include "LeaveRoomCommand.h"
 
LeaveRoomCommand::LeaveRoomCommand(int idPlayer):idPlayer(idPlayer){}
void LeaveRoomCommand::send(ProxyClient& proxy){
    proxy.sendLeaveRoom();
}