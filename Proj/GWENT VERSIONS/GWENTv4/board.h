#include "gwentCard.h"
#ifndef BOARD_H
#define BOARD_H
//Containing all elements of the game in the board structure
//To be able to save the state of the game in a binary file
struct Board {
//	int p1Health, p2Health;
	int turn;
	int round;
	int p2Left, p1Left;
//  int P2SAct, p1SAct;	
	int p1Dam, p2Dam;
	int p1Wins, p2Wins;
	int p1S, p1F, p1A;	//Index for player field
	int p2S , p2F, p2A; //Index for computer field
	bool gaming, match, p1Place, p2Place;
	Minion p1Arch [10], p1Fighter [10], p1Siege [10];
	Minion p2Arch [10], p2Fighter[10], p2Siege[10];
	//Card p1Spec, p2Spec;
	Minion *p1Hand;
	Minion *p2Hand;
	//Card fieldS[3];
	Minion *deck;
	/*~board(){
		delete []p1Hand;
		delete []p2Hand;
	}*/
};


#endif /* BOARD_H */
