#ifndef DADU_H
#define DADU_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

//DEFINISI TIPE
typedef struct {
	int dice1;
	int dice2;
} Dadu;

//SELEKTOR
#define Dice1(D) (D).dice1
#define Dice2(D) (D).dice2

int roll()
{
	Dadu D;
	Dice1(D)=(rand()%6)+1;
	Dice2(D)=(rand()%6)+1;
	return Dice1(D)+Dice2(D);
}


#endif