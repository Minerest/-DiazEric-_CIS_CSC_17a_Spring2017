#include <iostream>
#include <ctime>
#include <cstdlib>

#include "board.h"
#include "gwentCard.h"
using namespace std;

bool coinTos();
Card *setDeck(int);
Card *setHand(Card *, int);
void placeCard(Card &, board &);
void pntHand(board &, int);
void pntP1F(board &);
void pntP2F(board &);
void GwentAI(board &);

int main(int argc, char** argv) {
	srand(time(0));
	board b = {};
	//Set card type indexes to 0. Will add constructor function later
	b.p1S = 0;b.p1F=0;b.p1A=0;b.p2A=0;b.p2F=0;b.p2S=0;
	Card *deck;
	int size = 50, handSz = 10;
	int cho;
	bool gaming = true;
	deck = setDeck(size);
	b.p1Hand = setHand(deck, size);
	b.p2Hand = setHand(deck, size);
	b.p1Left = 10;
	b.p2Left = 10;
	do{//GAME LOOP
		cout<<"\nPLAYER 1 HAND"<<endl;
		pntHand(b, 1);
		cout<<"\nWhich card?\n";
		cin>>cho;
		if (cho < 0) {
			break;
		}
		else if (cho > 9){
			cout<<"Number is out of range!\n";
		}
		else if (!b.p1Hand[cho].getUsed()){
			placeCard(b.p1Hand[cho], b);
		}
		else{
			cout<<"That card has already been placed!\n";
		}
		cout<<"PLAYER 1 FIELD\n";
		pntP1F(b);
		cout<<"\nGETTING BEFORE AI\n";
		GwentAI(b);//Place AI card on the field
		cout<<"\nAFTER AI\n";
		cout<<"PLAYER 2 FIELD\n";
		pntP2F(b);
		if (b.p1Left == 0 || b.p2Left == 0) gaming = false;
		b.turn++;
	}while(gaming);	
	if (b.p2Dam > b.p1Dam){
		cout<<"\nYou LOSE!\n";
	}
	else
		cout<<"\nYOU WIN!!!\n";						
						//run fails when I delete pointers after running the game,
		  			    //but not when I quit the game right off the bat. Why is this?
					    //delete [] deck;// delete [] b.p1Hand; delete [] b.p2Hand;
	return 0;			
}

//===================================================================================================================================
//===================================================================================================================================


void pntP2F(board &b){
	cout<<"\nTOTAL DAMAGE: "<<b.p2Dam;
	cout<<"\nFIGHTERS: ";
	if (b.p2F!= 0){
		for (int i = 0; i < b.p2F; i++){
			cout<<" D:"<<b.p2Fighter[i].getDam()<<",   ";
		}
	}
	else
		cout<<"NONE PLACED!";
	cout<<"\nARCHERS: ";
	if (b.p2A != 0){
		for (int i = 0; i < b.p2A; i++){
			cout<<" D:"<<b.p2Arch[i].getDam()<<",   ";
		}
	}
	else
		cout<<"NONE PLACED!";
	cout<<"\nSIEGE UNITS: ";
	if (b.p2S != 0) {
		for (int i = 0; i < b.p2S; i++){
			cout <<" D:" << b.p2Siege[i].getDam() << ",   ";
		}
	}
	else{
		cout<<"NONE PLACED!\n";
	}
	cout<<endl;
}

void pntP1F(board &b){
	cout<<"\nTOTAL DAMAGE: "<<b.p1Dam;
	cout<<"\nFIGHTERS: ";
	if (b.p1F!= 0){
		for (int i = 0; i < b.p1F; i++){
			cout<<" D:"<<b.p1Fighter[i].getDam()<<",   ";
		}
	}
	else
		cout<<"NONE PLACED!";
	cout<<"\nARCHERS: ";
	if (b.p1A != 0){
		for (int i = 0; i < b.p1A; i++){
			cout<<" D:"<<b.p1Arch[i].getDam()<<",   ";
		}
	}
	else
		cout<<"NONE PLACED!";
	cout<<"\nSIEGE UNITS: ";
	if (b.p1S != 0) {
		for (int i = 0; i < b.p1S; i++){
			cout <<" D:" << b.p1Siege[i].getDam() << ",   ";
		}
	}
	else{
		cout<<"NONE PLACED!\n";
	}
	cout<<endl;
	return;
}

void pntHand(board &b, int player){
	cout<<"Index Damage   Type\n";
	if(player == 1){
		for (int i = 0; i < 10; i++){
			if(!b.p1Hand[i].getUsed()){
				cout<<i;//<<"    "<<b.p1Hand[i].getName();
				cout<<"     "<<b.p1Hand[i].getDam();
				cout<<"     "<<b.p1Hand[i].getType();
				cout<<endl;
			}
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			if (!b.p2Hand[i].getUsed()) {
				cout << i;// << "    " << b.p2Hand[i].getName();
				cout << "      " << b.p2Hand[i].getDam();
				cout << "      " << b.p2Hand[i].getType();
				cout << endl;
			}
		}
	}
}

void GwentAI(board &b){
	cout<<"INSIDE AI FunC";
	if (b.p2Dam > b.p1Dam + 3){	//Stops placing cards once AI has 5 point lead.
		cout<<"AI WINNING"<<endl;
		return;
	}
	char t;
	int rndPick;
	do{
		rndPick = rand()%10;	//pick random card from hand. I will change this to pick a card to get closer to the p1Damage+5 threshhold
	}while(b.p2Hand[rndPick].getUsed());
	t = b.p2Hand[rndPick].getType();
	switch (t) {
		case 'S':
			b.p2Siege[b.p2S] = b.p2Hand[rndPick];
			b.p2Dam += b.p2Siege[b.p2S].getDam();
			b.p2S++;
			break;
		case 'A':
			b.p2Arch[b.p2A] = b.p2Hand[rndPick];
			b.p2Dam += b.p2Arch[b.p2A].getDam();
			b.p2A++;
			break;
		case 'F':
			b.p2Fighter[b.p2F] = b.p2Hand[rndPick];
			b.p2Dam += b.p2Fighter[b.p2F].getDam();
			b.p2F++;
			break;
			//========================For Future versions =============================
		/*case 'f':
			b.fieldS[0] = card;
			break;
		case 'r':
			b.fieldS[1] = card;
			break;
		case 'i':
			b.fieldS[2] = card;
			break;*/
		default:
			break;
	}
	b.p2Left -= 1;
}



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
	b.p1Left -= 1;

		/*else{
			
			
			switch (t) {
				case 'S':
					b.p2Siege[index] = card;
					b.p2Dam += b.p2Siege[index].getDam();
					break;
				case 'A':
					b.p2Arch[index] = card;
					b.p2Dam += b.p2Arch[index].getDam();
					break;
				case 'F':
					b.p2Fighter[index] = card;
					b.p2Dam += b.p2Fighter[index].getDam();
					break;
//========================For Future versions =============================
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
					break; 			
			}
			b.p2Left -= 1;
		}*/
	card.setUsed(true);
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
	hand = new Card [15];
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