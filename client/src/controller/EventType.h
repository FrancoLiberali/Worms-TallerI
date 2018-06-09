#ifndef _EVENT_TYPE
#define _EVENT_TYPE 

enum EventType {
	START_TURN = 5,
	W_MOVE = 6,
	W_CHANGE_STATE = 7,
	B_POS = 8,
	B_EXPLOTE = 9,
	W_CUR_WEAPON = 10,
	W_CUR_AIM = 11,
	W_CHANGE_LIFE = 12,
	G_PLAYER_OFF = 13,
	G_PLAYER_WIN = 14,
};

#endif