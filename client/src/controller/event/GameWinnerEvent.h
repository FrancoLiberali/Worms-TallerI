#ifndef _GAME_WINNER_EVENT_H
#define _GAME_WINNER_EVENT_H

#include "Event.h"

class GameWinnerEvent : public Event {
private:
	int idPlayer;
public:
	GameWinnerEvent(int idPlayer);
	void process();
};

#endif