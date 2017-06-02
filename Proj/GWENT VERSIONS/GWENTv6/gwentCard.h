#ifndef GWENTCARD_H
#define GWENTCARD_H
#include <string>

class Card {
protected:
	char type;
	char *desc;
	char *name;
	int damage;
	int index;
	int mult;
	int sTurns;
	bool used;
	bool spec;	//if this card has a special ability, do something
public:
	int nmL;	
	void dblDam();
	void normDam();
	void setMult();
	void setTrns(bool);
	virtual void setName();
	void setType();
	void setZero();
	void setUsed(bool);
	char getType();
	char *getName();
	int getDam();
	bool getUsed();
	void pntName();
};

class Weather : public Card{
public:
	void setName();
};

class Minion : public Card{
public:
	int operator +(Minion &);
	void setDam();
	void setName();
	void allocate(int);
	void read(std::fstream &, int);//Getting desperate at finding a solution to the load/save game bug I've been having.
	void write(std::fstream &, int);//I was told that Minion::*getName() would return a COPY of this->name pointer so I figured
};									//writing a function to work directly with this->name pointer would solve my issues,
									//But I've hit a wall with no additional information: "RUN FAILED EXIT VALUE 1"

#endif /* GWENTCARD_H */

