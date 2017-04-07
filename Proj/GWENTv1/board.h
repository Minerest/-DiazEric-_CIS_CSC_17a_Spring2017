#include "gwentCard.h"
#ifndef BOARD_H
#define BOARD_H
//Containing all elements of the game in the board structure
//To be able to save the state of the game in a binary file

struct board {
//	int p1Health, p2Health;
	int turn;
	int round;
	int p2Left, p1Left;
//  int P2SAct, p1SAct;	
	int p1Dam, p2Dam;
	int p1S, p1F, p1A;	//Index for player field
	int p2S , p2F, p2A; //Index for computer field
	Card p1Arch [5], p1Fighter [5], p1Siege [5];
	Card p2Arch [5], p2Fighter[5], p2Siege[5];	//5 card maximum per field on board;
	Card p1Spec, p2Spec;
	Card *p1Hand;
	Card *p2Hand;
	Card fieldS[3];
};


#endif /* BOARD_H */
/*
 void placeCard(Card &card, board &b){
	char t;
	t = card.getType();
	switch (t){
		case 'S':
			b.p1Siege[b.p1S] = card;
			b.p1Dam += b.p1Siege[b.p1S].getDam();
			b.p1S++;
			break;
		case 'A':
			b.p1Arch[b.p1A] = card;
			b.p1Dam += b.p1Arch[b.p1A].getDam();
			b.p1A++;
			break;
		case 'F':
			b.p1Fighter[b.p1F] = card;
			b.p1Dam += b.p1Fighter[b.p1F].getDam();
			b.p1F++;
//========================For Future versions =============================
			break;
		case 'f':
				b.fieldS[0] = card;
			break;
		case 'r':
				b.fieldS[1] = card;
			break;
		case 'i':
				b.fieldS[2] = card;
			break;
		default:
			break; //snek			
	}
 
 */