#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

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
void GwentAI(board &, bool& placing);
void clrField(board &);
void GWENT();
void saveG(board &);
void loadG(board &);

int main(int argc, char** argv) {
	srand(time(0));
	board b = {};
	board clock[10];
	Card cClock[10][2][10];
	int size = 50, cnt = 0; 
	int cho;// user input
	GWENT();//Game base off The Witcher 3
	cout<<"Would you like to load the last saved game?\n";
	cout<<"press 0 for no, press 1 for yes\n";
	cin>>cho;
	if(cho == 1){
		loadG(b);
		pntP1F(b);
		cout << "===PLAYERFIELD ^====================AI FIELD v=============================================================================================\n";
		pntP2F(b);
	}
	else {
		b.p1Wins = 0;
		b.p2Wins = 0;
		b.gaming = true, b.match = true, b.p1Place = true, b.p2Place = true;
		b.deck = setDeck(size); //create the array of cards. ATM Random values per card
		b.p1Hand = setHand(b.deck, size); //Pick 10 cards from the deck
		b.p2Hand = setHand(b.deck, size); //There's a high chance to see a duplicate card
		b.p1Left = 10; //Cards left in the hand
		b.p2Left = 10;
	}
	do{//GAME LOOP
		do{
			if (cnt < 10){	//arbitrary number, it's rare rounds go on this long.
				clock[cnt] = b;	//save the state of the board
				for (int plyrs = 0; plyrs < 2; plyrs++){	//This would be a 3 line loop in python compared to 5 in C++ 
					for (int cards = 0; cards < 10; cards++){ //if you count the closing brackets as lines
						cClock[cnt][plyrs][cards] = (plyrs == 0)? b.p1Hand[cards]:b.p2Hand[cards];	//I could add a game counter and REALLY turn back the clock cClock[nGames][cnt][obj][card]									
					}
				}
			}
			if (b.p1Place){	//if the player can place cards
				cout<<"\nPLAYER 1"<<endl;
				pntHand(b, 1);	//print their hand of cards
				cout<<"\nWhich card?\n";
				cin>>cho;	
				if (cho == -1) {	//Player chooses to stop playing cards
					b.p1Place = false;
					cout<<"You cannot place cards until the next round\n";
				}
				else if (cho < -1) {//exit condition
					cout<<"EXITING GAME\n";
					saveG(b);	//Save game on quit
					b.gaming = false;
					b.match = false;
					cout << "PREDELETE\n";
					delete [] b.deck;
					cout<<"DELETE DECK\n";
					delete  b.p1Hand;
					cout<<"DELETE HAND1\n";
					delete [] b.p2Hand;
					cout << "DELETED\n";
					return 0;
				}
				else if (cho == 10){	//H4X
					do{
						cout<<"So you found the cheat, huh. How many turns would you like to turn back the clock?\n";
						cout<<"You can only turn back the clock up to 3 turns and the computer may play a different hand"<<endl;
						cout<<"CNT = "<<cnt;
						cin>>cho;
						if (cho == -1){	//Pretend the player never activated the cheat
							continue;
						}
					}while(cho > 3 || cho > cnt);	//How far did you think I'd let you rewind the game?
					b = clock[cnt-cho];		//rewind the board
					for (int i = 0; i <10; i++){	//for some reason, pointers in structs didn't work just by rewinding the board.
						b.p1Hand[i] = cClock[cnt-cho][0][i];
						b.p2Hand[i] = cClock[cnt-cho][1][i];
					}
					continue;	//TO THE TOP!
				}
				else if (cho > 10){//bounds checking
					cout<<"Number is out of range!\n";
				}
				else if (!b.p1Hand[cho].getUsed()){//check if the card has been placed
					placeCard(b.p1Hand[cho], b);	//place it!
				}
				else{
					cout<<"INVALID ENTRY!\n";
				}
			}
			cout<<"FIELD\n";
			pntP1F(b);//Print the player field
			if (b.p2Left>0)
				GwentAI(b, b.p2Place);//Place AI card on the field
			cout<<"===PLAYERFIELD ^====================AI FIELD v=======================================\n";
			pntP2F(b);//print AI field, will combine into 1 function later
			if (b.p2Left == 0)b.p2Place = false;
			if (b.p1Left == 0)b.p1Place = false;
			if (b.p1Place == false && b.p2Place == false)b.match = false;
			b.turn++;
			cnt++;
			cout<<"====================================================================================\n";
		}while(b.match);	//exit condition of the round loop
		b.p1Place = true;	//allow players to place cards again
		b.p2Place = true;
		b.match = true;		//start a new round
		if (b.p2Dam >= b.p1Dam){	//computer wins tie
			b.p2Wins++;
			cout<<"The AI has won the round!"<<endl;
			cout<<"You have "<<b.p1Wins<<" wins!\n";
			cout<<"The AI has "<<b.p2Wins<<" wins\n";
			cin>>cho;//breakpoint
		}
		else{
			b.p1Wins++;
			cout<<"You;ve win the round!"<<endl;
			cout<<"You have "<<b.p1Wins<<" wins!\n";
			cout<<"The AI has "<<b.p2Wins<<" wins\n";
			cin>>cho;//breakpoint
		}
		clrField(b);	//clear the field
		if (b.p2Wins == 2)	//Best 2 out of 3
			b.gaming = false;
		else if (b.p1Wins == 2)
			b.gaming = false;
		b.round++;		//keep track of nGames
	}while(b.gaming);	//Main game loop
	if (b.p2Wins > b.p1Wins)
		cout<<"\nYou LOSE!\n";
	else
		cout<<"\nYOU WIN!!!\n";						
						//run fails when I delete pointers after running the game,
		  			    //but not when I quit the game right off the bat. Why is this?
//					    ->delete [] deck;// delete [] b.p1Hand; delete [] b.p2Hand;
	//cout<<"PREDELETE\n";
	delete [] b.deck; delete [] b.p1Hand; delete [] b.p2Hand; 
	//cout<<"DELETED\n";
	return 0;			
}

//===================================================================================================================================
//===================================================================================================================================

void clrField(board &b){
	//Reset the playing field and indexes to 0;
	for (int i = 0;i < 10; i++){
		b.p1Arch[i].setZero();
		b.p1Fighter[i].setZero();
		b.p1Siege[i].setZero();
		b.p2Arch[i].setZero();
		b.p2Siege[i].setZero();
		b.p2Fighter[i].setZero();
	}
	b.p1S = 0;
	b.p1F = 0;
	b.p1A = 0;
	b.p2A = 0;
	b.p2F = 0;
	b.p2S = 0;
	b.p2Dam = 0;
	b.p1Dam = 0;
}
void pntP2F(board &b){
	cout<<"\nTOTAL DAMAGE: "<<b.p2Dam;
	cout<<"\nFIGHTERS: ";
	if (b.p2F!= 0){		//b.p2F is the index of the card array in the field
		for (int i = 0; i < b.p2F; i++){//b.p2F = 0 means there's no fighters in the field
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
	if (b.p1F!= 0){//array index on the field for the player
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
	if(player == 1){//prints out the cards you have in hand 
		for (int i = 0; i < 10; i++){
			if(!b.p1Hand[i].getUsed()){//if card has been used, don't show in hand
				cout<<i;//<<"    "<<b.p1Hand[i].getName();I'll make names later
				cout<<"     "<<b.p1Hand[i].getDam();
				cout<<"     "<<b.p1Hand[i].getType();
				cout<<endl;
			}
		}
	}
	else {
		for (int i = 0; i < 10; i++) {//This is for debugging. I'll delete it later
			if (!b.p2Hand[i].getUsed()) {
				cout << i;// << "    " << b.p2Hand[i].getName();
				cout << "      " << b.p2Hand[i].getDam();
				cout << "      " << b.p2Hand[i].getType();
				cout << endl;
			}
		}
	}
}

void GwentAI(board &b, bool& placing){//Places cards on the field from the 'AI'
	if (!placing)	return;
	if (b.p2Dam > b.p1Dam + 3){	//Stops placing cards once AI has 5 point lead.
		cout<<"AI WINNING"<<endl;//Prints something out so I know that the AI will stop
		placing = false;
		return;
	}
	char t;	//type. i.e. Fighter/Archer/Siege
	int rndPick, cnt=0;
	bool boo;
	do{
		cnt++;
		rndPick = rand()%10;	//pick random card from hand. I will change this to pick a card to get closer to the p1Damage+5 threshhold
	}while(b.p2Hand[rndPick].getUsed());	//Keep looping until you find something you haven't placed
	t = b.p2Hand[rndPick].getType();	//Fighter etc.
	switch (t) {	//Places the actual card on the field
		case 'S':
			b.p2Siege[b.p2S] = b.p2Hand[rndPick];
			b.p2Dam += b.p2Siege[b.p2S].getDam();
			b.p2S++;	//increases the index for the next placement.
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
	b.p2Hand[rndPick].setUsed(true);
	b.p2Left -= 1;	//keep track of how many cards they have on hand
}



void placeCard(Card &card, board &b){
	char t;
	t = card.getType();
	switch (t){//literally copy pasta from AI
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
				//b.fieldS[0] = card;
			break;
		case 'r':
				//b.fieldS[1] = card;
			break;
		case 'i':
				//b.fieldS[2] = card;
			break;
		default:
			break; //snek			
	}
	b.p1Left -= 1;
	card.setUsed(true);
	return;
}

Card *setDeck(int size){	//create deck
	Card *deck;	//pointer to Card class type
	deck = new Card [size];	//Can't delete this :(
	for (int i = 0; i < size; i++){	//random values for each card
		deck[i].setDam();			//Will make a deck with unique cards later
		deck[i].setName();
		deck[i].setType();
		deck[i].setUsed(false);
	}
	return deck;
}

Card *setHand(Card *deck, int size){	//create the hand
	Card *hand;		
	hand = new Card [10];	//can't delete this either
	for (int i = 0; i < 10; i++){
		hand[i] = deck[rand()%size];	//pick random card from deck
	}									//Will pick duplicates
	return hand;
}

void GWENT(){
	string t;
	char newL = '\n';
	ifstream g;
	g.open("GWENT.txt");	//Text art by http://patorjk.com/software/taag/
	while(!g.eof()){
		getline(g, t);	//get a character from GWENT.txt
		t+=newL;
		cout<<t;
	}
}

void saveG(board &b){
	fstream bin, hand1, hand2;
	bin.open("GWENTBIN.dat", ios::out | ios::binary);
	hand1.open("hand1.dat", ios::out | ios::binary);
	hand2.open("hand2.dat", ios::out | ios::binary);
	bin.write(reinterpret_cast<char *>(&b), sizeof(b));
	hand1.write(reinterpret_cast<char *>(&b.p1Hand[0]), sizeof(Card)*10);
	hand2.write(reinterpret_cast<char *> (&b.p2Hand[0]), sizeof(Card)*10);
	bin.close();
	hand1.close();
	hand2.close();
}

void loadG(board &b){
	fstream bin, hand1, hand2;
	bin.open("GWENTBIN.dat", ios::in | ios::binary);
	hand1.open("hand1.dat", ios::in | ios::binary);
	hand2.open("hand2.dat", ios::in | ios::binary);
	bin.read(reinterpret_cast<char *>(&b), sizeof(b));
	b.p1Hand = new Card [10];
	b.p2Hand = new Card [10];
	hand1.read(reinterpret_cast<char *> (&b.p1Hand[0]), sizeof (Card)*10);
	hand2.read(reinterpret_cast<char *> (&b.p2Hand[0]), sizeof (Card)*10);
	bin.close();
}

bool coinTos(){		//for future version of the game
	bool p1beg;
	p1beg = rand()%2;	// lol random number to set bool
	return p1beg;
}