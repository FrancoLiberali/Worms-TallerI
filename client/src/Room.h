#ifndef _ROOM_H
#define _ROOM_H

#include <string>
#include <map>

class Room {
private:
    int id;
    std::string name;
	int numPlayers;
    int currPlayers;
	std::string mapName;
    std::map<int, std::string> players;
public:
    Room(int idRoom, std::string& name, int numPlayers, std::string& map);
    int getId();
    int getNumPlayers();
    std::string getMap();
    std::string getName();
    void updateCurrPlayers(int currPlayers);
    int getCurrPlayers();
    bool isName(std::string& name);
};
#endif