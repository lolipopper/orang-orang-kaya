#include "dadu.h"

void roll()
{
	Dice1(D) = (rand() % 6) + 1;
	Dice2(D) = (rand() % 6) + 1;
}

boolean reroll()
{
	return Dice1(D) == Dice2(D);
}
