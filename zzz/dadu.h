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

//KAMUS GLOBAL
Dadu D; //dadu dalam permainan

//Spesififikasi
void roll(); //roll dadu

boolean reroll(); //boolean untuk menyatakan player dapat reroll atau tidak

#endif
