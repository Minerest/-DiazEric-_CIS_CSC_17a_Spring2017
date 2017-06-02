#ifndef GWENTCARD_H
#define GWENTCARD_H
class Card {
private:
	char type;
	char *name, *desc;
	int damage;
	int index;
	int mult;
	int sTurns;
	bool used;
	bool spec;	//if this card has a special ability, do something
public:
	void dblDam();
	void normDam();
	void setMult();
	void setTrns(bool);
	void setName();
	void setDam();
	void setType();
	void setZero();
	void setUsed(bool);
	char getType();
	char *getName();
	int getDam();
	bool getUsed();
	void pntName();

	//~Card();
};


#endif /* GWENTCARD_H */

