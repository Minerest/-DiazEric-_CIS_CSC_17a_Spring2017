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
	void read(std::fstream &, int);
	void write(std::fstream &, int);
};


#endif /* GWENTCARD_H */

