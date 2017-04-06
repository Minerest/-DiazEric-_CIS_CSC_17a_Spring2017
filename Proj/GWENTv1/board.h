#include "gwentCard.h"
#ifndef BOARD_H
#define BOARD_H

struct board {
	int p1Health;
	int p2Health;
	int turn;
	int p1SAct, p2SAct;
	int p1Left, p2Left;	//Cards left in the hand
	Card p1Arch [5], p1Sword [5], p1Siege [5], p2Arch [5], p2Sword[5], p2Siege[5];	//5 card maximum per field on board;
	Card p1Spec, p2Spec;
	Card *p1Hand;
	Card *p2Hand;
};


#endif /* BOARD_H */

