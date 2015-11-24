#ifndef OTHER_H
#define OTHER_H

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

// KONSTANTA
#define NMax 50

// DEFINISI TIPE
typedef struct {
	char TabKata[NMax];
	int	 Length;
} Kata;

typedef struct {
	int dice1;
	int dice2;
} Dadu;

Dadu D;

// SELEKTOR
#define Dice1(D) (D).dice1
#define Dice2(D) (D).dice2

boolean IsKataSama(Kata K1, Kata K2);
/* Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama dan
   urutan karakter yang menyusun kata juga sama. Sensitif terhadap uppercase dan lowercase */

void roll();
/* melakukan rolling dadu */

boolean reroll();
/* mengembalikan true jika pemain dapat melakukan reroll, false jika tidak
   pemain yang dapat melakukan reroll adalah pemain yang sebelum nya melakukan roll dengan dadu 1 = dadu 2 */

#endif
