#ifndef _EVENT_TYPE
#define _EVENT_TYPE 

enum EventType {
	W_MOVE = 3,
	START_TURN = 4,
	W_CHANGE_STATE = 5,
	B_POS = 6,
	B_EXPLOTE = 7,
	W_CUR_WEAPON = 8,
	W_CUR_AIM = 9,
	G_ENDGAME = 10,
};

#endif