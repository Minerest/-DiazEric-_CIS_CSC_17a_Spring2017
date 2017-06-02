#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include "gwentCard.h"
#include "board.h"

void Card::dblDam(){
	damage*=2;
	return;
}

void Card::normDam(){
	damage/=2;
	return;
}

void Minion::setDam(){
	damage = rand()%10+1;
}
void Card::setZero(){
	damage = 0;
}
void Card::setName(){
	std::string n = "PLACEHOLDER";
	this->name = new char[n.length()];//Should never call this function.
	for (int i = 0; i < n.length(); i++) {
		this->name[i] = n[i];
	}

}

void Weather::setName(){
	std::string t = "";	
	if (this->type == 'I'){	//Ice
		t = "FROST";
		this->name = new char[t.length()];
		for (int i = 0; i < t.length(); i++) {
			this->name[i] = t[i];
		}
	}
	else if (this->type =='C'){	//cloud
			t = "CLOUDS";
			for (int i = 0; i < t.length(); i++) {
			this->name[i] = t[i];
			}
		}
	else{
		t = "RAIN";
		this->name = new char[t.length()];
		for (int i = 0; i < t.length(); i++) {
			this->name[i] = t[i];
		}
	}
}

void Minion::setName(){//Creates random name for Minion object
	
	int vwlMx = 5; //5 vowels in english alphabet
	int cnstMx = 26-5;	//all letters in alphabet - vowels
	int rnd, lnS1,lnS2, nmLn = 3+(int)rand()%3;
	std::string stuff, stuff2;
	char *vowels, *cnst, t;
	stuff = "aeiou";
	stuff2 = "bcdfghjklmnpqrstvwxyz";
	lnS1 = stuff.length();
	lnS2 = stuff2.length();
	vowels = new char [lnS1];
	this->name = new char [nmLn];
	this->name[0] = rand()%2 == 1? stuff[rand()%lnS1]-32:stuff2[rand()%lnS2]-32;
	for (int i = 0; i < lnS1; i++) {
		vowels[i] = stuff[i];
	}
	cnst = new char [lnS2];
	for (int i = 0; i < lnS2; i++) {
		cnst[i] = stuff2[i];
	}
	for (int i = 1; i < nmLn; i++) {
		rnd = rand() % 2 + 1;
		if (rand()%2 == 1){
			for (int j = 0; j < rnd; j++){
				t = vowels[rand()%vwlMx];
				this->name[i] = t;
			}
		}
		else{
			for (int j = 0; j < rnd; j++){
				t = cnst[rand()%cnstMx];
				this->name[i]=t;
			}
		}
	}
}

void Card::setUsed(bool b){
	this->used = b;
}

void Card::setType(){
	int j;
	j = rand()%3;
	switch(j){
		case 0:
			type = 'S';	//Siege unit
			break;
		case 1:
			type = 'A';	//Archer unit
			break;
		case 2:
			type = 'F';	//Fighter unit
			break;
		case 3:	//Next version of the game
			type = 'f';	//fog special
			break;
		case 4: 
			type = 'r';	//rain special
			break;
		case 5:
			type = 'i';	//ice special
		default:
			break;
			//cout<<"Should not hit default gwentCard.cpp Card::setType()"<<endl;
	}
}

void Card::setTrns(bool boo){
	if (boo){
		sTurns = 3;
	}
}

bool Card::getUsed(){
	return used;
}
char *Card::getName(){
	return this->name;
}

char Card::getType(){
	return type;
}

int Card::getDam(){
	return damage;
}
