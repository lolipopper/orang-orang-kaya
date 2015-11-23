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

#endif
