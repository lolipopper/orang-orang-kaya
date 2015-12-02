#include "other.h"

int main()
{
	roll();
	printf("Melakukan lempar dadu : ");
	printf("%d %d\n",Dice1(D),Dice2(D));

	roll();
	printf("Melakukan lempar dadu : ");
	printf("%d %d\n",Dice1(D),Dice2(D));
	printf("Reroll jika dadu tidak sama : ");
	printf("%d\n",reroll());
	Dice2(D)=Dice1(D);
	printf("Reroll jika dadu tidak sama : ");
	printf("%d\n",reroll());

	help();

	return 0;
}
