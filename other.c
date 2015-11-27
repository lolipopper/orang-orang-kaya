#include "other.h"

boolean IsKataSama(Kata K1, Kata K2)
{
	int i;

	if (K1.Length == K2.Length) {
		i=0;
		while ((i<K1.Length) && (K1.TabKata[i]==K2.TabKata[i])) {
			i++;
		}
		if (i == K1.Length) {
            return true;
		}
		else {
            return false;
		}
	}
	else {
        return false;
	}
}

void roll()
{
    srand ( time(NULL) );
	Dice1(D) = (rand() % 6) + 1;
	Dice2(D) = (rand() % 6) + 1;
	//Dice1(D) = 2;
	//Dice2(D) = 5;
}

boolean reroll()
{
	return Dice1(D) == Dice2(D);
}
