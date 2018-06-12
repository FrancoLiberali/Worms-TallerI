#ifndef _GAME_WINNER_EVENT_H
#define _GAME_WINNER_EVENT_H

#include "Event.h"

class GameWinnerEvent : public Event {
private:
	int idPlayer;
    mainView& view;
    Model& model;
public:
	GameWinnerEvent(int idPlayer, Model& model, mainView& view);
	void process();
};

#endif