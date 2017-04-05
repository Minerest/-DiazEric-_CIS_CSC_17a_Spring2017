#include<string>

#ifndef INVENTORY_H
#define INVENTORY_H
struct inventory {
	char dtAdded[10];
	char name[20];
	int Q;	//Quantity
	float wCost;
	float rCost;
	int record;
};


#endif /* INVENTORY_H */

