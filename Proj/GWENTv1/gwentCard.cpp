#include <cstdlib>

#include "gwentCard.h"
void Card::dblDam(){
	damage*=2;
	return;
}

void Card::normDam(){
	damage/=2;
	return;
}

void Card::setDam(){
	damage = rand()%10+1;
}

void Card::setName(){
	name = new char [10];
	for (int i = 0; i < 10; i++){
		name[i] = 'A'+rand()%24;
	}
}

void Card::setUsed(bool b){
	used = b;
}

void Card::setType(){
	int j;
	j = rand()%6;
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
		case 3:
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
	return name;
}

char Card::getType(){
	return type;
}

int Card::getDam(){
	return damage;
}

Card::~Card(){
	delete [] name;
	if (desc) delete [] desc;
}