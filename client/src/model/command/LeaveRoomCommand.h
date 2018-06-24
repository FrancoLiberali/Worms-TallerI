#ifndef _LEAVE_ROOM_COMMAND_H
#define _LEAVE_ROOM_COMMAND_H

#include "ClientCommand.h"

class LeaveRoomCommand : public ClientCommand{
private:
    int idPlayer;
public:
    LeaveRoomCommand(int idPlayer);
    void send(ProxyClient& proxy);
};

#endif