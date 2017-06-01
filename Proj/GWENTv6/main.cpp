#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>

#include "Board.h"
#include "gwentCard.h"
using namespace std;

//Who needs globals when you can just pass around a struct?!
Minion *setDeck(const int);	//creates a deck of Minions
Minion *setHand(Minion *, const int);//creates a new minion ptr in each player hand and sets it equal to random cards in the deck
void placeCard(Minion &, Board &);//places a Minion from player 1 onto the field
void pntHand(Board &, const int);//prints the hand
void pntP1F(Board &);//prints the field where all Minions are
void pntP2F(Board &);
void dblD(Board &);		//Overloading the [+] operator. Chance for a Minion to do double damage
void GwentAI(Board &, bool& placing);	//AI placement.... Now with beefier AI
void clrField(Board &);	//clears the field.
void GWENT();//prints some text art
void saveG(Board &);//serializes the game in binary files
void loadG(Board &);//loads game from binary files
void newG(Board &);//starts a new game.

int main(int argc, char** argv) {	
	srand(time(0));
	Board b = {};
	Board clock[10];
	Minion cClock[10][2][10];		//NOW WITH 3D EFFECTS
	int cnt = 0; 
	int cho;// user input
	bool again;
	
	
	GWENT();  //Game based off The Witcher 3
	cout<<"Would you like to load the last saved game?\n";
	cout<<"press 0 for no, press 1 for yes\n";
	cin>>cho;
	if(cho == 1){
		//load game from binary files
		cout<<"PRELOAD\n";
		loadG(b);
		pntP1F(b);
		cout << "=== ^====================AI FIELD v=============================================================================================\n";
		pntP2F(b);
	}
	else {
		newG(b);	//Do you want to play a game?
	}
	do{
		do{//GAME LOOP
			do{//match loop
				if (cnt < 10){	//amount of cards in hand, it's rare rounds go on this long. Also bounds check to prevent going over allocated memory.
					clock[cnt] = b;	//save the state of the Board
					for (int plyrs = 0; plyrs < 2; plyrs++){	
						for (int cards = 0; cards < 10; cards++){ 
							cClock[cnt][plyrs][cards] = (plyrs == 0)? b.p1Hand[cards]:b.p2Hand[cards];	//I could add a game counter and REALLY turn back the clock cClock[nGames][cnt][obj][card], but why stop there?									
						}
					}
				}
				//Condition check at the beginning to see if players can continue to place cards.
				if (b.p2Left == 0)b.p2Place = false;
				if (b.p1Left == 0)b.p1Place = false;
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
						cout << "PREDELETE\n";									  //I had a bad bug here
						for (int i = 0; i < 50; i++)delete [] b.deck[i].getName();//Fixing it helped me understand the concept of ownership.
						delete [] b.deck;										  //Had to wrap my mind around the fact that 2 variables were pointing to the same piece of data.
						cout<<"DELETED DECK\n";
						delete []b.p1Hand;
						delete []b.p2Hand;
						cout<<"DELETED HANDS!";
						return 0;
					}
					else if (cho == 10 && cnt >=3){	//H4X
						do{
							cout<<"So you found the cheat, huh. How many turns would you like to turn back the clock?\n";
							cout<<"You can only turn back the clock up to 3 turns and the computer may play a different hand"<<endl;
							cout<<"CNT = "<<cnt<<endl;
							cin>>cho;
							if (cho == -1){	//Pretend the player never activated the cheat
								continue;
							}
						}while(cho > 3 || cho > cnt);	//How far did you think I'd let you rewind the game?
						b = clock[cnt-cho];		//rewind the Board
						for (int i = 0; i <10; i++){	//for some reason, pointers in structs didn't work just by rewinding the Board.
							b.p1Hand[i] = cClock[cnt-cho][0][i];
							b.p2Hand[i] = cClock[cnt-cho][1][i];
							
						}
						continue;	//TO THE TOP!
					}
					else if (cho > 10){//bounds checking
						cout<<"Number is out of range!\n";
						continue;
					}
					else if (!b.p1Hand[cho].getUsed()){//check if the card has been placed
						placeCard(b.p1Hand[cho], b);	//place it!
					}
					else{
						cout<<"INVALID ENTRY!\n";
						continue;
					}
				}
				cout<<"FIELD\n";
				pntP1F(b);//Print the player field
				if (b.p2Left>0)
					GwentAI(b, b.p2Place);//Place AI card on the field
				pntP2F(b);//print AI field, will combine into 1 function later
				b.turn++;
				cnt++;
				cout<<"====================================================================================\n";
				if (b.p1Place == false && b.p2Place == false)b.match = false; //break out once both players stop placing cards
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
			cout << "\nYou LOSE!\n";
		else
			cout << "\nYOU WIN!!!\n";	
		cout<<"Press 1 to play again"<<endl;
		cin>>cho;
		again = cho == 1 ? true: false;
		GWENT();	//This file is best run on a GTX 1080 graphics card with at least 8gb of ram.
		for (int i = 0; i < 50; i++) delete []b.deck[i].getName();
		delete [] b.deck;
		delete [] b.p1Hand;
		delete [] b.p2Hand;
		if (again) newG(b);
	}while(again);	
						//SUPER weird bug, the game deletes fine both on new and load games HERE
	return 0;			// But the game crashes when you close the game early after you load the game.
}						// Figured out the bug, the new pointers in the name don't save to the files easily
						// so if I tried delete[] b.deck[i].getName()), it crashes since there's no allocated memory
						// Best way to learn is to crash and burn!
//===================================================================================================================================
//===================================================================================================================================

void clrField(Board &b){
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
void pntP2F(Board &b){
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

void pntP1F(Board &b){
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

void pntHand(Board &b, const int player){
	cout<<"Index"<<setw(8)<<"Damage"<<setw(8)<<"Type"<<setw(8)<<"Name\n";
	if(player == 1){//prints out the cards you have in hand 
		for (int i = 0; i < 10; i++){
			if(!b.p1Hand[i].getUsed()){//if card has been used, don't show in hand
				cout<<i;
				cout<<setw(8)<<b.p1Hand[i].getDam();
				cout<<setw(8)<<b.p1Hand[i].getType();
				cout<<setw(10)<<b.p1Hand[i].getName();
				cout<<endl;
			}
		}
	}
	else {
		for (int i = 0; i < 10; i++) {//This is for debugging. I'll delete it later
			if (!b.p2Hand[i].getUsed()) {
				cout << i;
				cout << setw(8)<< b.p2Hand[i].getDam();
				cout << setw(8)<< b.p2Hand[i].getType();
				cout << setw(8) << b.p2Hand[i].getUsed();
				cout << endl;
			}
		}
	}
}

template <class T>	//This is weird, do I really define templates here? There's no function prototype or anything. I'd love to know what's the standard convention
T isDonePlacing(T pDam, T cDam){
	if (cDam > pDam+3){
		return true;
	}
	return false;
}

void GwentAI(Board &b, bool& placing){//Places cards on the field from the 'AI'
	if (!placing)	return;
	if (b.p1Place == false && b.p2Dam > b.p1Dam){
		placing = false;
		return;
	}
	if (isDonePlacing(b.p1Dam, b.p2Dam)){	//Stops placing cards once AI has 3 point lead or if it lost a round.
		placing = false;
		return;
	}
	char t;	//type. i.e. Fighter/Archer/Siege
	int delta, deltaZ = 11, ind = 0;;
	bool boo;
	delta = b.p1Dam - b.p2Dam;
	if (b.p1Wins == 0 && b.turn > 3 && delta > 10)
	cout<<"Delta = "<<delta<<endl;
	if (delta > 0){
		for (int i = 0; i < 10; i++){
			if (b.p2Hand[i].getUsed()) 
				continue;	//skip placed cards
			
			if (b.p2Hand[i].getDam() > delta && b.p2Hand[i].getDam() < deltaZ){
				deltaZ = b.p2Hand[i].getDam();
				ind = i;
			}
		}
	}
	else{
		for (int i = 0; i < 10; i++){
			if (b.p2Hand[i].getUsed())
				continue;
			if (b.p2Hand[i].getDam() < deltaZ){
				deltaZ = b.p2Hand[i].getDam();
				ind = i;
			}
		}
	}

	
//	do{
//		rndPick = rand()%10;	//pick random card from hand. I will change this to pick a card to get closer to the p1Damage+3 threshhold
//	}while(b.p2Hand[rndPick].getUsed());	//Keep looping until you find something you haven't placed

	t = b.p2Hand[ind].getType();	//Fighter etc.
	switch (t) {	//Places the actual card on the field
		case 'S':
			b.p2Siege[b.p2S] = b.p2Hand[ind];
			b.p2Dam += b.p2Siege[b.p2S].getDam();
				b.p2S++;	//increases the index for the next placement.
				break;
			case 'A':
				b.p2Arch[b.p2A] = b.p2Hand[ind];
				b.p2Dam += b.p2Arch[b.p2A].getDam();
				b.p2A++;
				break;
			case 'F':
			b.p2Fighter[b.p2F] = b.p2Hand[ind];
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
	b.p2Hand[ind].setUsed(true);
	b.p2Left -= 1;	//keep track of how many cards they have on hand
}

void dblD(Board &b){
	int r = rand()%3, rndMin, bonusD = 0; //Pick a random unit type
	if (b.turn < 2) return;
	if (r == 0){
		if (b.p1S!= 0){
			rndMin = rand()%b.p1S;
			bonusD = (b.p1Siege[rndMin] + b.p1Siege[rndMin]);
			cout<<b.p1Siege[rndMin].getName()<<" has gained a significant advantage! It now deals a large amount of bonus damage";
		}
		else return;
	}
	else if (r == 1){
		if (b.p1A != 0){
			rndMin = rand()%b.p1A;
			bonusD = b.p1Arch[rndMin] + b.p1Arch[rndMin];
			cout<<b.p1Arch[rndMin].getName() << " has gained a significant advantage! It now deals a large amount of bonus damage";
		}
		else return;
	}
	bonusD*=0.8;
	cout<<"BONUS DAMAGE = "<<bonusD<<endl;
	cout<<"BOARD DAMAGE = "<<b.p1Dam<<endl;
	//Swordsman cannot get an advantage
	b.p1Dam += bonusD;
}

void placeCard(Minion &card, Board &b){
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
		case 'C':
				//b.fieldS[0] = card;
			break;
		case 'R':
				//b.fieldS[1] = card;
			break;
		case 'I':
				//b.fieldS[2] = card;
			break;
		default:
			break; //snek			
	}
	if (rand()%7 == 5) dblD(b);	//1 in 7 chance to get an advantage. AI is too stronk
	b.p1Left -= 1;
	card.setUsed(true);
	return;
}

Minion *setDeck(const int size){	//create deck
	Minion *deck;	//pointer to Card class type
	deck = new Minion[size];
	for (int i = 0; i < size; i++){	//random values for each card
		deck[i].setDam();//Will make a deck with unique cards later
		deck[i].setName();
		deck[i].setType();
		deck[i].setUsed(false);
	}
	return deck;
}

Minion *setHand(Minion *deck, const int size){	//create the hand
	Minion *hand;		
	hand = new Minion [10];	
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
		getline(g, t);
		t+=newL;
		cout<<t;
	}
	g.close();
}

void saveG(Board &b){
	fstream bin, hand1, hand2, deck, nm1, nm2;
	nm1.open("nm1.dat",ios::out);
	nm2.open("nm2.dat",ios::out);
	deck.open("DECK.dat",ios::out | ios::binary);
	bin.open("GWENTBIN.dat", ios::out | ios::binary);
	hand1.open("hand1.dat", ios::out | ios::binary);
	hand2.open("hand2.dat", ios::out | ios::binary);
	
	
	deck.write(reinterpret_cast<char *>(&b.deck[0]), sizeof(Minion)*50);
	bin.write(reinterpret_cast<char *>(&b), sizeof(b));
	hand1.write(reinterpret_cast<char *>(&b.p1Hand[0]), sizeof(Minion)*10);
	hand2.write(reinterpret_cast<char *> (&b.p2Hand[0]), sizeof(Minion)*10);
	
	
	for (int i = 0; i < 10; i++){
		cout<<i<<"   ";
		cout<<b.p1Hand[i].getName()<<"   ";
		cout<<b.p2Hand[i].getName()<<endl;
		nm1 << b.p1Hand[i].getName()<< ' ';
		nm2 << b.p2Hand[i].getName() << ' ';
		
//		nm1.write(b.p1Hand[i].getName(), b.p1Hand[i].nmL);
//		nm2.write(b.p2Hand[i].getName(), b.p2Hand[i].nmL);
	}
	
	nm1.close();
	nm2.close();
	bin.close();
	hand1.close();
	hand2.close();
	deck.close();
}

void loadG(Board &b){
	fstream bin, hand1, hand2, deck, nm1,nm2;
	int hndSz = 10;
	
	//open files
	nm1.open("nm1.dat", ios::in);
	nm2.open("nm2.dat", ios::in);
	deck.open("DECK.dat", ios::in | ios::binary);
	bin.open("GWENTBIN.dat", ios::in | ios::binary);
	hand1.open("hand1.dat", ios::in | ios::binary);
	hand2.open("hand2.dat", ios::in | ios::binary);
	
	b.deck = new Minion[50];
	b.p1Hand = new Minion [hndSz];
	b.p2Hand = new Minion [hndSz];
	
	bin.read(reinterpret_cast<char *> (&b), sizeof (b));
	deck.read(reinterpret_cast<char *>(&b.deck[0]), sizeof(Minion)*50);
	hand1.read(reinterpret_cast<char *> (&b.p1Hand[0]), sizeof (Minion)*hndSz);
	hand2.read(reinterpret_cast<char *> (&b.p2Hand[0]), sizeof (Minion)*hndSz);
	
	for (int i = 0; i < hndSz; i++){	//Allocate memory based on the name size.
		cout<<i<<"   ";
		b.p1Hand[i].allocate(b.p1Hand[i].nmL);
		b.p2Hand[i].allocate(b.p2Hand[i].nmL);
		b.p1Hand[i].read(nm1, b.p1Hand[i].nmL); //nm1.read(this->name, nameSize);
		b.p2Hand[i].read(nm2, b.p2Hand[i].nmL);
		cout<<b.p2Hand[i].getName()<<"    ";
		cout<<b.p1Hand[i].getName()<<endl;
	}

	cout<<"PRECLOSE\n";
	bin.close();
	cout<<"BINCLOSE\n";
	hand1.close();
	hand2.close();	
	cout<<"HANDSCLOSE\n";
	deck.close();
	cout<<"DECKCLOSE\n";
	nm1.close();
	nm2.close();
	cout<<"CLOSED\n";
}

void newG(Board &b) {
	int size = 50;
	b.p1Wins = 0;
	b.p2Wins = 0;
	b.gaming = true, b.match = true, b.p1Place = true, b.p2Place = true;
	b.deck = setDeck(size); //create the array of cards. atm Random values per card
	b.p1Hand = setHand(b.deck, size); //Pick 10 cards from the deck
	b.p2Hand = setHand(b.deck, size); //There's a high chance to see a duplicate card
	b.p1Left = 10; //amount of cards left in the hand
	b.p2Left = 10;
	b.p1Dam = 0;
	b.p2Dam = 0;
}
