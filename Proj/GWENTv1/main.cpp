#include <iostream>
#include <ctime>
#include <cstdlib>

#include "board.h"
#include "gwentCard.h"
using namespace std;

bool coinTos();
Card *setDeck(int);
Card *setHand(Card *, int);
void placeCard(Card, board &, int, int, char);
void pntHand(board &, int);


int main(int argc, char** argv) {
	srand(time(0));
	board b = {};
	Card *deck;
	int size = 50, handSz = 10;
	deck = setDeck(size);
	b.p1Hand = setHand(deck, size);
	b.p2Hand = setHand(deck, size);
	b.p1Left = 10;
	b.p2Left = 10;

	delete [] deck;		//is this necessary? I have a destructor function in the class Card.
	return 0;			//Does this also call the destructor for every Card in the pointer?
			
}
















//===================================================================================================================================
void pntHand(board &b, int player){
	if(player == 1){
		for (int i = 0; i < b.p1Left; i++){
			
		}
	}
}

void placeCard(Card card, board &b, int player, int index){

	return;
}

Card *setDeck(int size){
	Card *deck;
	deck = new Card [size];
	for (int i = 0; i < size; i++){
		deck[i].setDam();
		deck[i].setName();
		deck[i].setType();
		deck[i].setUsed(false);
	}
	return deck;
}

Card *setHand(Card *deck, int size){
	Card *hand;
	hand = new Card [10];
	for (int i = 0; i < 10; i++){
		hand[i] = deck[rand()%size];
	}
	return hand;
}

bool coinTos(){
	bool p1beg;
	p1beg = rand()%2;
	return p1beg;
}