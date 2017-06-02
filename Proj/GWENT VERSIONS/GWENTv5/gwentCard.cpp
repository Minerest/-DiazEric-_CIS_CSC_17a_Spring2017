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
	//bug: The names aren't created correctly the first time around, however after the game repeats, the names are generated as intended. I hate C++.
	//bug fix: You have to add the null terminator manually. I still hate C++
	
	int vwlMx = 5; //5 vowels in english alphabet
	int cnstMx = 26-5;	//all letters in alphabet - vowels
	int rnd, lnS1,lnS2, nmLn = 3+rand()%3;
	char *vowels, *cnst, t;
	char stuff[] = "aeiou";
	char stuff2[] = "bcdfghjklmnpqrstvwxyz";
	vowels = new char [26];
	cnst = new char [26];
	this->name = new char [nmLn+1];
	
	//These next 2 loops are the results of pulling my hair out while trying to figure out what was going on.
	for (int i = 0; i < 5; i++) {
		vowels[i] = stuff[i];
	}
	vowels[5]='\0';
	for (int i = 0; i < 21; i++) {
		cnst[i] = stuff2[i];	
	}
	cnst[21] = '\0';
	this->name[0] = rand() % 2 == 1 ? vowels[rand() % 5] - 32 : cnst[rand() % 21] - 32; //pick if the name starts with const or a vowel
	
	for (int i = 1; i < nmLn; i++) {
		rnd = rand() % 2 + 1;
		if (rand()%2 == 1){
			for (int j = 0; j < rnd; j++){	//Did some reading, I guess this is called a deep copy.
				this->name[i] = vowels[rand()%vwlMx];//It's needed because I needed to create a copy of the chosen letter to a section
			}										// of memory that doesn't just disappear upon exiting the function.
		}
		else{
			for (int j = 0; j < rnd; j++){
				this->name[i]= cnst[rand()%cnstMx];
			}
		}
	}
	this->name[nmLn] = '\0';
	std::cout<<this->name<<std::endl;
	delete [] vowels;	//I know I don't have to allocate memory all the time like this,
	delete [] cnst;		//but after getting some error "can't use '=' operator on type (char) and type (char *),
}						//I just tried setting the arrays to the same type. This problem helped me understand memory allocation a little deeper.

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

int Minion::operator +(Minion &right){
	return this->getDam() + right.getDam();
}